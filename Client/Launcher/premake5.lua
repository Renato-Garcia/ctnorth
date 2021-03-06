project "Launcher"
    language "C++"
    kind "WindowedApp"
    targetname "CTNorth"
    targetdir(buildpath("."))
    debugdir(buildpath("."))

    pchheader "Precompiled.hpp"
    pchsource "Precompiled.cpp"

    entrypoint "wmainCRTStartup"
    editandcontinue "Off"
    largeaddressaware "On" -- largeaddressaware(true)
    flags { "NoIncrementalLink" }
    linkoptions "/IGNORE:4254 /OPT:NOLBR /SAFESEH:NO /DYNAMICBASE:NO /LAST:.zdata"

    links
    {
        "Base",
        "dbghelp", "psapi", "comctl32", "wininet", "winhttp", "Shlwapi"
    }

    vpaths
    {
        ["Headers/*"] = "**.hpp",
        ["Sources/*"] = "**.cpp",
        ["Resources/*"] = {"**.rc", "res/*.ico"},
        ["*"] = "premake5.lua"
    }

    files
    {
        "premake5.lua",
        "*.hpp",
        "*.cpp",
        "**.rc"
    }

    -- TODO: Version management
    files "res/ctn-canary.ico"

    filter "architecture:x64"
        flags { "ExcludeFromBuild" }

    filter "system:not windows"
        flags { "ExcludeFromBuild" }
