// DamageAtomicModelInfo.hpp
// Author(s):       iFarbod <>
//
// Copyright (c) 2015-2017 CTNorth Team
//
// Distributed under the MIT license (See accompanying file LICENSE or copy at
// https://opensource.org/licenses/MIT)

#pragma once

#include "Common.hpp"
#include "AtomicModelInfo.hpp"

namespace ctn::SA
{

class CDamageAtomicModelInfo : public CAtomicModelInfo
{
public:
    struct RpAtomic* m_damagedAtomic;
};

VALIDATE_SIZE(CDamageAtomicModelInfo, 0x24)

}
