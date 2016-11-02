// Swaps two values
// Author(s):       iFarbod <ifarbod@outlook.com>
//
// Copyright (c) 2015-2016 The San Andreas Online Open Source Project
//
// Distributed under the MIT license (See accompanying file LICENSE or copy at
// https://opensource.org/licenses/MIT)

#pragma once

namespace Util
{

// Swap two values.
template <class T>
inline void Swap(T& first, T& second)
{
    T temp = first;
    first = second;
    second = temp;
}

}