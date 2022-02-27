
#include <exec/libraries.h>
#include <exec/emulation.h>

#define __USE_INLINE__

#include <stdio.h>
#include <proto/exec.h>
#include <proto/dos.h>

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
	printf("%s:%s:%ld\n",__FILE__,__FUNCTION__,__LINE__);
	return 0UL;
}

STATIC ULONG stub_IdExpansion_ppc(ULONG *regarray)
{
	printf("%s:%s:%ld\n",__FILE__,__FUNCTION__,__LINE__);
	ULONG TagList = (ULONG) regarray[REG68K_A0/4];

	return (ULONG) regarray[REG68K_D0/4];
}

STATIC STRPTR stub_IdHardware_ppc(ULONG *regarray)
{
	printf("%s:%s:%ld\n",__FILE__,__FUNCTION__,__LINE__);
	ULONG Type = (ULONG) regarray[REG68K_D0/4];
	ULONG TagList = (ULONG) regarray[REG68K_A0/4];

	return (STRPTR) regarray[REG68K_D0/4];
}

STATIC LONG stub_IdAlert_ppc(ULONG *regarray)
{
	printf("%s:%s:%ld\n",__FILE__,__FUNCTION__,__LINE__);
	ULONG Type = (ULONG) regarray[REG68K_D0/4];
	ULONG TagList = (ULONG) regarray[REG68K_A0/4];

	return (LONG) regarray[REG68K_D0/4];
}

STATIC LONG stub_IdFunction_ppc(ULONG *regarray)
{
	printf("%s:%s:%ld\n",__FILE__,__FUNCTION__,__LINE__);
	STRPTR LibName = (STRPTR) regarray[REG68K_A0/4];
	ULONG Offset = (ULONG) regarray[REG68K_D0/4];
	ULONG TagList = (ULONG) regarray[REG68K_A1/4];

	return (LONG) regarray[REG68K_D0/4];
}

STATIC ULONG stub_IdHardwareNum_ppc(ULONG *regarray)
{
	printf("%s:%s:%ld\n",__FILE__,__FUNCTION__,__LINE__);
	ULONG Type = (ULONG) regarray[REG68K_D0/4];
	ULONG TagList = (ULONG) regarray[REG68K_A0/4];

	return (ULONG) regarray[REG68K_D0/4];
}

STATIC void stub_IdHardwareUpdate_ppc(ULONG *regarray)
{
	printf("%s:%s:%ld\n",__FILE__,__FUNCTION__,__LINE__);
}

STATIC ULONG stub_IdFormatString_ppc(ULONG *regarray)
{
	printf("%s:%s:%ld\n",__FILE__,__FUNCTION__,__LINE__);
	STRPTR String = (ULONG) regarray[REG68K_A0/4];
	ULONG Buffer = (ULONG) regarray[REG68K_A1/4];
	ULONG Length = (ULONG) regarray[REG68K_D0/4];
	ULONG Tags = (ULONG) regarray[REG68K_A2/4];

	return (ULONG) regarray[REG68K_D0/4];
}

STATIC ULONG stub_IdEstimateFormatSize_ppc(ULONG *regarray)
{
	printf("%s:%s:%ld\n",__FILE__,__FUNCTION__,__LINE__);
	STRPTR String = (ULONG) regarray[REG68K_A0/4];
	ULONG Tags = (ULONG) regarray[REG68K_A1/4];
	return (ULONG) regarray[REG68K_D0/4];
}

