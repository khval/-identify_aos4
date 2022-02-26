/*
* identify.library
*
* Copyright (C) 2022 Kjetil Hvalstrand
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdbool.h>
#include <exec/exec.h>
#include <proto/exec.h>
#include <dos/dos.h>
#include <exec/types.h>
#include <libraries/kittyCompact.h>
#include <proto/kittyCompact.h>
#include <stdarg.h>

/****** kittyCompact/main/Release ******************************************
*
*   NAME
*      Release -- Description
*
*   SYNOPSIS
*      ULONG Release(void);
*
*   FUNCTION
*
*   INPUTS
*
*   RESULT
*       The result ...
*
*   EXAMPLE
*
*   NOTES
*
*   BUGS
*
*   SEE ALSO
*
*****************************************************************************
*
*/

ULONG _Identify_Release(struct kittyCompactIFace *Self)
{
    return --Self -> Data.RefCount;
}

