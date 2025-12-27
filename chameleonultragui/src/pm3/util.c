//-----------------------------------------------------------------------------
// Copyright (C) Proxmark3 contributors. See AUTHORS.md for details.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// See LICENSE.txt for the text of the license.
//-----------------------------------------------------------------------------
// utilities
//-----------------------------------------------------------------------------

#include "util.h"

// global client debug variable
uint8_t g_debugMode = 0;
// global client disable logging variable
uint8_t g_printAndLog = PRINTANDLOG_PRINT | PRINTANDLOG_LOG;
// global client tell if a pending prompt is present

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// determine number of logical CPU cores (use for multithreaded functions)
// determine number of logical CPU cores (use for multithreaded functions)
int num_CPUs(void)
{
    int count = 1;
#if defined(_WIN32)
#include <sysinfoapi.h>
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    count = sysinfo.dwNumberOfProcessors;
#else
    count = sysconf(_SC_NPROCESSORS_ONLN);
    if (count <= 0)
        count = 1;
#endif

    // Optimization: Don't use all cores to prevent system freeze (CPU explosion)
    // If we have many cores, spare 2 for OS/UI. If few, spare 1.
    if (count > 6) {
        return count - 2;
    } else if (count > 1) {
        return count - 1;
    }
    return count;
}
