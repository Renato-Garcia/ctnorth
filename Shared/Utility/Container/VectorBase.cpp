// Vector base
// Author(s):       iFarbod <ifarbod@outlook.com>
//
// Copyright (c) 2015-2017 CTNorth Team
//
// Distributed under the MIT license (See accompanying file LICENSE or copy at
// https://opensource.org/licenses/MIT)

#include <PCH.hpp>

#include "VectorBase.hpp"

namespace ctn
{

unsigned char* VectorBase::AllocateBuffer(unsigned size)
{
    return new unsigned char[size];
}

}
