// Vehicle audio entity
// Author(s):       iFarbod <>
//
// Copyright (c) 2015-2017 CtNorth Team
//
// Distributed under the MIT license (See accompanying file LICENSE or copy at
// https://opensource.org/licenses/MIT)

#pragma once

#include "Common.hpp"

namespace ctn::SA
{

struct CAEVehicleAudioEntity
{
    u8 pad[0x24C];
};

VALIDATE_SIZE(CAEVehicleAudioEntity, 0x24C);

}
