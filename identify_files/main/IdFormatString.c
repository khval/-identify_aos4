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


#include <exec/exec.h>
#include <proto/exec.h>
#include <dos/dos.h>
#include <exec/types.h>
#include <libraries/identify.h>
#include <proto/identify.h>
#include <stdarg.h>

/****** identify/main/IdFormatString ******************************************
*
*   NAME
*      IdFormatString -- Description
*
*   SYNOPSIS
*      void IdFormatString(STRPTR str1, STRPTR str2, struct TagItem * Tags);
*
*   FUNCTION
*
*   INPUTS
*       str1 - 
*       str2 - 
*       Tags - 
*
*   RESULT
*       This function does not return a result
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

void _Identify_IdFormatString(struct IdentifyIFace *Self,
       STRPTR str1, STRPTR str2,  struct TagItem * Tags)
{
}

