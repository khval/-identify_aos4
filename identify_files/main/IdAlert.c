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

#define __USE_INLINE__
#include  <proto/dos.h>

/****** identify/main/IdAlert ******************************************
*
*   NAME
*      IdAlert -- Description
*
*   SYNOPSIS
*      LONG IdAlert(ULONG value, struct TagItem * Tags);
*
*   FUNCTION
*
*   INPUTS
*       value - 
*       Tags - 
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

LONG _Identify_IdAlert(struct IdentifyIFace *Self,
       ULONG value,
       struct TagItem * Tags)
{
	Printf("Aleart: %08lx\n",value);
  return 0;
}

