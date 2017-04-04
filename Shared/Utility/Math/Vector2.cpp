// Two-dimensional vector
// Author(s):       iFarbod <ifarbod@outlook.com>
//
// Copyright (c) 2015-2017 CTNorth Team
//
// Distributed under the MIT license (See accompanying file LICENSE or copy at
// https://opensource.org/licenses/MIT)

#include <PCH.hpp>

#include <Math/Vector2.hpp>

namespace ctn
{

const Vector2 Vector2::ZERO;
const Vector2 Vector2::LEFT{ -1.0f, 0.0f };
const Vector2 Vector2::RIGHT{ 1.0f, 0.0f };
const Vector2 Vector2::UP{ 0.0f, 1.0f };
const Vector2 Vector2::DOWN{ 0.0f, -1.0f };
const Vector2 Vector2::ONE{ 1.0f, 1.0f };

const IntVector2 IntVector2::ZERO;

String Vector2::ToString() const
{
    return String::Format("%g %g", m_x, m_y);
}

String IntVector2::ToString() const
{
    return String::Format("%d %d", m_x, m_y);
}

}
