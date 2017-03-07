// 2D Rectangle
// Author(s):       iFarbod <ifarbod@outlook.com>
//
// Copyright (c) 2015-2017 CtNorth Team
//
// Distributed under the MIT license (See accompanying file LICENSE or copy at
// https://opensource.org/licenses/MIT)

#include "Rect.hpp"

namespace ctn::SA
{

CRect::CRect() :
    left_(0.0f),
    top_(0.0f),
    right_(0.0f),
    bottom_(0.0f)
{
}

CRect::CRect(f32 left, f32 top, f32 right, f32 bottom) :
    left_(left),
    top_(top),
    right_(right),
    bottom_(bottom)
{
}

}
