// Timed model info
// Author(s):       iFarbod <>
//
// Copyright (c) 2015-2017 CTNorth Team
//
// Distributed under the MIT license (See accompanying file LICENSE or copy at
// https://opensource.org/licenses/MIT)

#pragma once

#include "Common.hpp"
#include "AtomicModelInfo.hpp"
#include "TimeInfo.hpp"

namespace ctn::SA
{

class CTimeModelInfo : public CAtomicModelInfo
{
public:
    CTimeInfo m_timeInfo;
};

VALIDATE_SIZE(CTimeModelInfo, 0x24);

}
