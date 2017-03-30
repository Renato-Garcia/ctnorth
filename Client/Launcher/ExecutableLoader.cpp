// PE32 Executable loader
// Author(s):       iFarbod <ifarbod@outlook.com>
//                  NTAuthority
//
// Copyright (c) 2015-2017 CtNorth Team
//
// Distributed under the MIT license (See accompanying file LICENSE or copy at
// https://opensource.org/licenses/MIT)

#include "Precompiled.hpp"
#include "Main.hpp"

#include <Math/MathDefs.hpp>

ExecutableLoader::ExecutableLoader(const uint8_t* origBinary)
{
    m_origBinary = origBinary;
    m_loadLimit = UINT_MAX;

    SetLibraryLoader([](const char* name)
    {
        return LoadLibraryA(name);
    });

    SetFunctionResolver([](HMODULE module, const char* name)
    {
        return reinterpret_cast<LPVOID>(GetProcAddress(module, name));
    });
}

bool ExecutableLoader::LoadDependentLibraries(IMAGE_NT_HEADERS* ntHeader)
{
    IMAGE_DATA_DIRECTORY* importDirectory = &ntHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];

    IMAGE_IMPORT_DESCRIPTOR* descriptor = GetTargetRVA<IMAGE_IMPORT_DESCRIPTOR>(importDirectory->VirtualAddress);

    while (descriptor->Name)
    {
        const char* name = GetTargetRVA<char>(descriptor->Name);

        HMODULE module = ResolveLibrary(name);

        if (!module)
        {
            FatalError(va("Could not load dependent module %s. Error code was %i.", name, GetLastError()));
            return false;
        }

        if (reinterpret_cast<unsigned>(module) == 0xFFFFFFFF)
        {
            descriptor++;
            continue;
        }

        auto nameTableEntry = GetTargetRVA<unsigned>(descriptor->OriginalFirstThunk);
        auto addressTableEntry = GetTargetRVA<unsigned>(descriptor->FirstThunk);

        while (*nameTableEntry)
        {
            FARPROC function;
            const char* functionName;

            if (IMAGE_SNAP_BY_ORDINAL(*nameTableEntry))
            {
                function = reinterpret_cast<FARPROC>(
                    ResolveLibraryFunction(module, MAKEINTRESOURCEA(IMAGE_ORDINAL(*nameTableEntry))));
                functionName = va("#%d", IMAGE_ORDINAL(*nameTableEntry));
            }
            else
            {
                auto import = GetTargetRVA<IMAGE_IMPORT_BY_NAME>(*nameTableEntry);

                function = reinterpret_cast<FARPROC>(ResolveLibraryFunction(module, (const char*)import->Name));
                functionName = static_cast<const char*>(import->Name);
            }

            if (!function)
            {
                char pathName[MAX_PATH];
                GetModuleFileNameA(module, pathName, sizeof(pathName));

                FatalError(va("Could not load function %s in dependent module %s (%s).", functionName, name, pathName));
                return false;
            }

            *addressTableEntry = reinterpret_cast<unsigned>(function);

            nameTableEntry++;
            addressTableEntry++;
        }

        descriptor++;
    }

    return true;
}

void ExecutableLoader::LoadSection(IMAGE_SECTION_HEADER* section)
{
    void* targetAddress = GetTargetRVA<uint8_t>(section->VirtualAddress);
    const void* sourceAddress = m_origBinary + section->PointerToRawData;

    if ((uintptr_t)targetAddress >= m_loadLimit)
    {
        FatalError("Exceeded load limit.");
        return;
    }

    if (section->SizeOfRawData > 0)
    {
        DWORD oldProtect;
        unsigned sizeOfData = ctn::Min(section->SizeOfRawData, section->Misc.VirtualSize);

        VirtualProtect(targetAddress, sizeOfData, PAGE_EXECUTE_READWRITE, &oldProtect);
        memcpy(targetAddress, sourceAddress, sizeOfData);
    }
}

void ExecutableLoader::LoadSections(IMAGE_NT_HEADERS* ntHeader)
{
    IMAGE_SECTION_HEADER* section = IMAGE_FIRST_SECTION(ntHeader);

    for (int i = 0; i < ntHeader->FileHeader.NumberOfSections; i++)
    {
        // Load the given section into memory
        LoadSection(section);

        section++;
    }
}

void ExecutableLoader::LoadIntoModule(HMODULE module)
{
    m_executableHandle = module;

    IMAGE_DOS_HEADER* header = (IMAGE_DOS_HEADER*)m_origBinary;

    if (header->e_magic != IMAGE_DOS_SIGNATURE)
    {
        return;
    }

    IMAGE_DOS_HEADER* sourceHeader = (IMAGE_DOS_HEADER*)module;
    IMAGE_NT_HEADERS* sourceNtHeader = GetTargetRVA<IMAGE_NT_HEADERS>(sourceHeader->e_lfanew);

    IMAGE_NT_HEADERS* ntHeader = (IMAGE_NT_HEADERS*)(m_origBinary + header->e_lfanew);

    LoadSections(ntHeader);
    LoadDependentLibraries(ntHeader);

    m_entryPoint = GetTargetRVA<void>(ntHeader->OptionalHeader.AddressOfEntryPoint);

    DWORD oldProtect;
    VirtualProtect(sourceNtHeader, 0x1000, PAGE_EXECUTE_READWRITE, &oldProtect);

    sourceNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT] = ntHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
}

HMODULE ExecutableLoader::ResolveLibrary(const char* name)
{
    return m_libraryLoader(name);
}

LPVOID ExecutableLoader::ResolveLibraryFunction(HMODULE module, const char* name)
{
    return m_functionResolver(module, name);
}
