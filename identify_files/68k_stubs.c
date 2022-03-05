

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <exec/libraries.h>
#include <exec/emulation.h>
#include "../locale/locale.h"


#define __USE_INLINE__

#include <stdio.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <utility/tagitem.h>
#include <libraries/identify.h>

#undef Close
#undef Open

STATIC APTR stub_Open_ppc(ULONG *regarray);
STATIC APTR stub_Close_ppc(ULONG *regarray);
STATIC APTR stub_Expunge_ppc(ULONG *regarray);
STATIC ULONG stub_Reserved_ppc(ULONG *regarray);

STATIC ULONG stub_IdExpansion_ppc(ULONG *regarray);
STATIC STRPTR stub_IdHardware_ppc(ULONG *regarray);
STATIC LONG stub_IdAlert_ppc(ULONG *regarray);
STATIC LONG stub_IdFunction_ppc(ULONG *regarray);
STATIC ULONG stub_IdHardwareNum_ppc(ULONG *regarray);
STATIC void stub_IdHardwareUpdate_ppc(ULONG *regarray);
STATIC ULONG stub_IdFormatString_ppc(ULONG *regarray);
STATIC ULONG stub_IdEstimateFormatSize_ppc(ULONG *regarray);

const struct EmuTrap stub_Open = { TRAPINST, TRAPTYPE, (void *) stub_Open_ppc };
const struct EmuTrap stub_Close = { TRAPINST, TRAPTYPE, (void *) stub_Close_ppc };
const struct EmuTrap stub_Expunge = { TRAPINST, TRAPTYPE, (void *) stub_Expunge_ppc };
const struct EmuTrap stub_Reserved = { TRAPINST, TRAPTYPE, (void *) stub_Reserved_ppc };

const struct EmuTrap stub_IdExpansion = { TRAPINST, TRAPTYPE, (void *) stub_IdExpansion_ppc };
const struct EmuTrap stub_IdHardware = { TRAPINST, TRAPTYPE, (void *) stub_IdHardware_ppc };
const struct EmuTrap stub_IdAlert = { TRAPINST, TRAPTYPE, (void *) stub_IdAlert_ppc };
const struct EmuTrap stub_IdFunction = { TRAPINST, TRAPTYPE, (void *) stub_IdFunction_ppc };
const struct EmuTrap stub_IdHardwareNum = { TRAPINST, TRAPTYPE, (void *) stub_IdHardwareNum_ppc };
const struct EmuTrap stub_IdHardwareUpdate = { TRAPINST, TRAPTYPE, (void *) stub_IdHardwareUpdate_ppc };
const struct EmuTrap stub_IdFormatString = { TRAPINST, TRAPTYPE, (void *) stub_IdFormatString_ppc };
const struct EmuTrap stub_IdEstimateFormatSize = { TRAPINST, TRAPTYPE, (void *) stub_IdEstimateFormatSize_ppc };

const ULONG VecTable68K[] = {
	(ULONG) &stub_Open,
	(ULONG) &stub_Close,
	(ULONG) &stub_Expunge,
	(ULONG) &stub_Reserved,
	(ULONG) &stub_IdExpansion,
	(ULONG) &stub_IdHardware,
	(ULONG) &stub_IdAlert,
	(ULONG) &stub_IdFunction,
	(ULONG) &stub_IdHardwareNum,
	(ULONG) &stub_IdHardwareUpdate,
	(ULONG) &stub_IdFormatString,
	(ULONG) &stub_IdEstimateFormatSize,
	(ULONG)-1
};

ULONG get_osver();
ULONG get_wbver();
void get_powerpc_clock_str();
const char *get_locale_str(uint32 id);
ULONG IdHardwareNum_ppc(ULONG type, struct TagItem *TagList);
void IdFormatString(const char *String, char *Buffer, ULONG BufferLength);

STATIC APTR stub_Open_ppc(ULONG *regarray)
{
	struct Library *Base = (struct Library *) regarray[REG68K_A6/4];
	struct ExtendedLibrary *ExtLib = (struct ExtendedLibrary *) ((ULONG)Base + Base->lib_PosSize);
	struct LibraryManagerInterface *Self = (struct LibraryManagerInterface *) ExtLib->ILibrary;

	regarray[REG68K_D0/4] = (ULONG) Self -> Open( 0);

	return (APTR) regarray[REG68K_D0/4];
}

STATIC APTR stub_Close_ppc(ULONG *regarray)
{
	struct Library *Base = (struct Library *) regarray[REG68K_A6/4];
	struct ExtendedLibrary *ExtLib = (struct ExtendedLibrary *) ((ULONG)Base + Base->lib_PosSize);
	struct LibraryManagerInterface *Self = (struct LibraryManagerInterface *) ExtLib->ILibrary;

	regarray[REG68K_D0/4] = (ULONG) Self -> Close();

	return (APTR) regarray[REG68K_D0/4];
}

STATIC APTR stub_Expunge_ppc(ULONG *regarray)
{
	return NULL;
}

STATIC ULONG stub_Reserved_ppc(ULONG *regarray)
{
	return 0UL;
}

STATIC ULONG stub_IdExpansion_ppc(ULONG *regarray)
{
	ULONG TagList = (ULONG) regarray[REG68K_A0/4];
	return (ULONG) regarray[REG68K_D0/4];
}

STATIC STRPTR stub_IdHardware_ppc(ULONG *regarray)
{
	return (STRPTR) IdHardware_ppc((ULONG) regarray[REG68K_D0/4], (struct TagItem *) regarray[REG68K_A0/4]);
}

STATIC LONG stub_IdAlert_ppc(ULONG *regarray)
{
	ULONG Type = (ULONG) regarray[REG68K_D0/4];
	ULONG TagList = (ULONG) regarray[REG68K_A0/4];

	return (LONG) regarray[REG68K_D0/4];
}

STATIC LONG stub_IdFunction_ppc(ULONG *regarray)
{
	STRPTR LibName = (STRPTR) regarray[REG68K_A0/4];
	ULONG Offset = (ULONG) regarray[REG68K_D0/4];
	ULONG TagList = (ULONG) regarray[REG68K_A1/4];

	return (LONG) regarray[REG68K_D0/4];
}

void dump_taglist(struct TagItem *tag)
{
	while (tag -> ti_Tag != TAG_END)
	{
		printf("Tag: %08x,Data: %08x\n", (int) tag -> ti_Tag,(int)  tag->ti_Data);
		tag ++;
	}
}

STATIC ULONG stub_IdHardwareNum_ppc(ULONG *regarray)
{
	regarray[REG68K_D0/4] = IdHardwareNum_ppc( (ULONG) regarray[REG68K_D0/4], (struct TagItem *) regarray[REG68K_A0/4]);
	return (ULONG) regarray[REG68K_D0/4];
}

STATIC void stub_IdHardwareUpdate_ppc(ULONG *regarray)
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
}

STATIC ULONG stub_IdFormatString_ppc(ULONG *regarray)
{
	STRPTR String = (STRPTR) regarray[REG68K_A0/4];
	char * Buffer = (char *) regarray[REG68K_A1/4];
	ULONG Length = (ULONG) regarray[REG68K_D0/4];

	IdFormatString( String, Buffer, Length);
	regarray[REG68K_D0/4] = strlen(Buffer);
	return (ULONG) regarray[REG68K_D0/4];
}

int IdEstimateFormatSize(const char *String);

STATIC ULONG stub_IdEstimateFormatSize_ppc(ULONG *regarray)
{
	regarray[REG68K_D0/4] = IdEstimateFormatSize( (const char *) regarray[REG68K_A0/4] );
	return (ULONG) regarray[REG68K_D0/4];
}

