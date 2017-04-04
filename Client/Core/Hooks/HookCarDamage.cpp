// Car damage bug fix
// Author(s):       iFarbod <ifarbod@outlook.com>
//                  Silent <zdanio95@gmail.com>
//
// Copyright (c) 2015-2017 CTNorth Team
//
// Distributed under the MIT license (See accompanying file LICENSE or copy at
// https://opensource.org/licenses/MIT)

#include "Precompiled.hpp"
#include <Hooking/Hook.hpp>
#include <Hooking/HookFunction.hpp>

using namespace ctn;
using namespace ctn::Hook;

void __declspec(naked) CarDamageFix()
{
    __asm
    {
        fldz
        fcomp[esp + 20h + 10h]
        fnstsw ax
        test ah, 5
        jp FixedCarDamage_Negative
        movzx eax, byte ptr[edi + 21h]
        retn

    FixedCarDamage_Negative:
        movzx eax, byte ptr[edi + 24h]
        retn
    }
}

static HookFunction hookFunction([]()
{
    // Fix car damage bug
    MakeCall(0x5428EA, CarDamageFix);
});
