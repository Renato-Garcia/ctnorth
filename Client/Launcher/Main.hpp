// Linker configuration
// Author(s):       iFarbod <ifarbod@outlook.com>
//
// Copyright (c) 2015-2017 CTNorth Team
//
// Distributed under the MIT license (See accompanying file LICENSE or copy at
// https://opensource.org/licenses/MIT)

#pragma once

#include <windows.h>

#include <stdint.h>
#include <stdio.h>

#include <io.h>
#include <Commdlg.h>
#include <Shlwapi.h>

#include "Utils.hpp"
#include "ExecutableLoader.hpp"

#include "GameLauncher.hpp"

#define CTN_REG_KEY HKEY_CURRENT_USER
#define CTN_REG_SUBKEY "SOFTWARE\\CTNorth"

#define GAME_EXECUTABLE_NAME "gta_sa.exe"

extern char g_gamePath[MAX_PATH];
extern char g_gameExecutable[MAX_PATH];
extern char g_executablePath[MAX_PATH];
