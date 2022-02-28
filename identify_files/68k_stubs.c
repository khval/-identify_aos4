
#include <exec/libraries.h>
#include <exec/emulation.h>

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
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	return 0UL;
}

STATIC ULONG stub_IdExpansion_ppc(ULONG *regarray)
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	ULONG TagList = (ULONG) regarray[REG68K_A0/4];

	return (ULONG) regarray[REG68K_D0/4];
}

STATIC STRPTR stub_IdHardware_ppc(ULONG *regarray)
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	ULONG Type = (ULONG) regarray[REG68K_D0/4];
	ULONG TagList = (ULONG) regarray[REG68K_A0/4];

	return (STRPTR) regarray[REG68K_D0/4];
}

STATIC LONG stub_IdAlert_ppc(ULONG *regarray)
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	ULONG Type = (ULONG) regarray[REG68K_D0/4];
	ULONG TagList = (ULONG) regarray[REG68K_A0/4];

	return (LONG) regarray[REG68K_D0/4];
}

STATIC LONG stub_IdFunction_ppc(ULONG *regarray)
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
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


ULONG get_powerpc()
{
	uint32 model;

	GetCPUInfoTags( GCIT_Model, &model, TAG_DONE);
	
	switch (model)
	{
		case CPUTYPE_UNKNOWN:
			return 0;

		case CPUTYPE_PPC603E:
			return IDPPC_603E;

		case CPUTYPE_PPC604E:
			return IDPPC_604E;

		default:
			return (model - CPUTYPE_PPC750CXE) + IDPPC_750CXE;
	}
	return 0;
}

ULONG get_powerpc_clock()
{
	uint64 frequency;
	GetCPUInfoTags( GCIT_ProcessorSpeed, &frequency, TAG_DONE);
	return (ULONG) (frequency);
}

ULONG get_osver()
{
	char buffer[30];
	int32 len = GetVar("kickstart",buffer,30,GVF_GLOBAL_ONLY);
	if (len)
	{
		printf("%s\n",buffer);
	}
}

ULONG get_wbver()
{
	char buffer[30];
	int32 len = GetVar("workbench",buffer,30,GVF_GLOBAL_ONLY);
	if (len)
	{
		printf("%s\n",buffer);
	}
}


ULONG IdHardwareNum_ppc(ULONG type, struct TagItem *TagList)
{
	ULONG ret = 0;

	switch (type)
	{
		case IDHW_SYSTEM:
			ret = IDSYS_AmigaONE_X1000;
			break;

		case IDHW_CPU:
			ret = IDCPU_68020;
			break;

		case IDHW_FPU:
			ret = IDFPU_68882;
			break;

		case IDHW_MMU:
			ret = IDMMU_68060;
			break;

		case IDHW_POWERPC:
			ret = get_powerpc();
			break;

		case IDHW_POWERFREQ:
			ret = 0;
			break;

		case IDHW_PPCCLOCK:
			ret = get_powerpc_clock();
			break;

		case IDHW_PPCOS:
			ret = IDPOS_AmigaOS_PPC;
			break;

		case IDHW_AUDIOSYS:
			ret = IDAOS_AHI;
			break;

		case IDHW_GARY:
			ret = IDGRY_NONE;
			break;

		case IDHW_RAMSEY:
			ret = IDRSY_NONE ;
			break;

		case IDHW_AGNUS:
			ret = IDAG_NONE;
			break;

		case IDHW_DENISE:
			ret = IDDN_NONE;
			break;

		case IDHW_AGNUSMODE:
			ret = IDAM_NONE;
			break;

		case IDHW_TCPIP:
			ret = IDTCP_ROADSHOW;
			break;

		case IDHW_OSNR:
			ret = IDOS_4_1;
			break;

		case IDHW_GFXSYS:
			ret = IDGOS_PICASSO96;
			break;

		case IDHW_OSVER:
			ret = get_osver();
			break;

		case IDHW_WBVER:
			ret = get_wbver();
			break;
	}

	return ret;
}

STATIC ULONG stub_IdHardwareNum_ppc(ULONG *regarray)
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	regarray[REG68K_D0/4] = IdHardwareNum_ppc( (ULONG) regarray[REG68K_D0/4], (struct TagItem *) regarray[REG68K_A0/4]);

	return (ULONG) regarray[REG68K_D0/4];
}

STATIC void stub_IdHardwareUpdate_ppc(ULONG *regarray)
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
}

STATIC ULONG stub_IdFormatString_ppc(ULONG *regarray)
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	STRPTR String = (ULONG) regarray[REG68K_A0/4];
	ULONG Buffer = (ULONG) regarray[REG68K_A1/4];
	ULONG Length = (ULONG) regarray[REG68K_D0/4];
	ULONG Tags = (ULONG) regarray[REG68K_A2/4];

	return (ULONG) regarray[REG68K_D0/4];
}

STATIC ULONG stub_IdEstimateFormatSize_ppc(ULONG *regarray)
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	STRPTR String = (ULONG) regarray[REG68K_A0/4];
	ULONG Tags = (ULONG) regarray[REG68K_A1/4];
	return (ULONG) regarray[REG68K_D0/4];
}

