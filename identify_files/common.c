
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <utility/tagitem.h>
#include <libraries/identify.h>

#define __USE_INLINE__

#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/expansion.h>
#include <proto/version.h>
#include <proto/timer.h>

#include "tools.h"

char chipram[10];
char fastram[10];
char vmmram[10];
char vmmchipram[10];
char totalram[10];
char execver[30];
char eclock_str[30];
char vblackfreq_str[30];
char powerfreq_str[30];

char osver[30];
char wbver[30];
char ppc_clock_str[30];
const char *str_na = "N/A";
const char *str_true = "TRUE";
const char *str_false = "FALSE";
const char *str_none = "NONE";
const char *str_yes = "YES";
const char *str_no = "NO";

extern struct PCIIFace *IPCI;

extern const char *get_locale_str(uint32 id);


ULONG IdHardwareNum_ppc(ULONG type, struct TagItem *TagList)
{
	uint32 mret = 0;
	ULONG ret = 0;

	switch (type)
	{
		case IDHW_SYSTEM:

			GetMachineInfoTags( GMIT_Machine, &mret, TAG_END);

			switch (mret)
			{
    				case MACHINETYPE_UNKNOWN:
					ret = IDSYS_Unknown;
					break;

    				case MACHINETYPE_BLIZZARDPPC:
					ret = IDSYS_AMIGA1200;
					break;

    				case MACHINETYPE_CYBERSTORMPPC:
					ret = IDSYS_AMIGA4000;
					break;

    				case MACHINETYPE_AMIGAONE:
					ret = IDSYS_AmigaONE;
					break;

    				case MACHINETYPE_SAM440:
					ret = IDSYS_Sam440;
					break;

    				case MACHINETYPE_SAM460:
					ret = IDSYS_Sam460;
					break;

    				case MACHINETYPE_X1000:
					ret = IDSYS_AmigaONE_X1000;
					break;

    				case MACHINETYPE_CHUNYE:
					ret = IDSYS_AmigaONE_X1222;
					break;

    				case MACHINETYPE_X5000_20:
					ret = IDSYS_AmigaONE_X5020;
					break;

    				case MACHINETYPE_X5000_40:
					ret = IDSYS_AmigaONE_X5040;
					break;

    				case MACHINETYPE_PEGASOS2:
					ret = IDSYS_Pegasus_II;
					break;
			}
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

		case IDHW_VBLANKFREQ:
			ret = (struct ExecIFace *)(*(struct ExecBase **)4) -> VBlankFrequency;
			break;

		case IDHW_POWERPC:
			ret = get_powerpc();
			break;

		case IDHW_POWERFREQ:
			ret = (struct ExecIFace *)(*(struct ExecBase **)4) -> PowerSupplyFrequency;
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

		case IDHW_EXECVER:
			ret = (struct ExecIFace *)(*(struct ExecBase **)4) -> SoftVer;
			break;

		case IDHW_CHIPRAM:
			ret =  AvailMem(MEMF_TOTAL|MEMF_CHIP);
			break;

		case IDHW_FASTRAM:
			ret = AvailMem(MEMF_TOTAL|MEMF_FAST);
			break;

		case IDHW_VMMFASTRAM:
			ret = AvailMem(MEMF_TOTAL|MEMF_VIRTUAL);
			break;

		case IDHW_VMMRAM:
			ret = AvailMem(MEMF_TOTAL|MEMF_VIRTUAL);
			break;

		case IDHW_ECLOCK:
			{
				struct EClockVal eclock;
				ret = ReadEClock( &eclock );
			}
			break;
	}

	return ret;
}

const char *get_str(ULONG type, ULONG id)
{
	const char *ret = str_na;

	switch (type)
	{
		case IDHW_SYSTEM:
			GetMachineInfoTags( GMIT_MachineString,&ret, TAG_END);
			break;

		case IDHW_CPU:
			ret=get_locale_str(5000+id);	break;

		case IDHW_FPU:
			ret=id ? get_locale_str(5008+id) : str_none;
			break;

		case IDHW_MMU:
			ret=id ? str_yes : str_no;	break;

		case IDHW_POWERPC:
			ret=get_locale_str(7000+id);	break;

		case IDHW_VBLANKFREQ:
			get_clock_str(id, vblackfreq_str);
			ret = vblackfreq_str;
			break;

		case IDHW_POWERFREQ:
			get_clock_str(id, powerfreq_str);
			ret = powerfreq_str;
			break;

		case IDHW_PPCCLOCK:
			get_powerpc_clock_str();
			ret = ppc_clock_str;
			break;

		case IDHW_PPCOS:
			ret=GetOSString();	break;

		case IDHW_AUDIOSYS:
			ret=get_locale_str(5700+id);	break;

		case IDHW_GARY:
			ret=id ? str_true: str_false;	break;

		case IDHW_RAMSEY:
			ret=id ? str_true: str_false;	break;

		case IDHW_AGNUS:
			ret=id ? str_true: str_false;	break;

		case IDHW_DENISE:
			ret=id ? str_true: str_false;	break;

		case IDHW_AGNUSMODE:
			ret=id ? str_true: str_false;	break;

		case IDHW_TCPIP:
			ret=id ? str_true: str_false;	break;

		case IDHW_OSNR:
			ret=GetReleaseString();	break;

		case IDHW_GFXSYS:
			ret=get_locale_str(5500+id);	break;


		case IDHW_EXECVER:
			sprintf(execver,"%d", (struct ExecIFace *)(*(struct ExecBase **)4) -> SoftVer);
			ret = execver;
			break;

		case IDHW_OSVER:
			get_osver();
			ret = osver;
			break;

		case IDHW_WBVER:
			get_wbver();
			ret = wbver;
			break;


		case IDHW_PLNCHIPRAM:
		case IDHW_CHIPRAM:
			ram_to_str(AvailMem(MEMF_TOTAL|MEMF_CHIP),chipram);
			ret = chipram;
			break;

		case IDHW_PLNFASTRAM:
		case IDHW_FASTRAM:
			ram_to_str(AvailMem(MEMF_TOTAL|MEMF_FAST),fastram);
			ret = fastram;
			break;

		case IDHW_PLNRAM:
			ram_to_str(AvailMem(MEMF_TOTAL),totalram);
			ret = totalram;
			break;

		case IDHW_VMMCHIPRAM:
			ram_to_str(0,vmmchipram);
			ret = vmmchipram;
			break;

		case IDHW_VMMRAM:
		case IDHW_VMMFASTRAM:
			ram_to_str(AvailMem(MEMF_TOTAL|MEMF_VIRTUAL),vmmram);
			ret = vmmram;
			break;

		case IDHW_ECLOCK:
			get_clock_str(id, eclock_str);
			ret = eclock_str;
			break;
	}

	return ret;
}

const char *IdHardware_ppc(ULONG type, struct TagItem *TagList)
{
	ULONG id;
	id = IdHardwareNum_ppc( (ULONG) type, (struct TagItem *) TagList);
	return get_str((ULONG) type, id);
}

extern const char *str_tags[];

LONG get_tag_id(const char *tag);

void IdFormatString(const char *String, char *Buffer, ULONG BufferLength)
{
	LONG l,id;
	const char *c,*r, *sc;
	char *d;
	char *BufferE = Buffer + BufferLength-1;

	d = Buffer;
	for (c=String;*c;)
	{
		l = 1;

		if (*c=='$')
		{
			id = get_tag_id(c);

			if (id!=-1)
			{
				l = strlen(str_tags[id]);				
				r = IdHardware_ppc( id, NULL );
				if (r) for (sc = r;(*sc)&&(d<BufferE);*d++=*sc++);
			}
		}

		if (l==1)
		{
			if (d<BufferE)
			{
				*d++ = *c++;
			}
			else c++;
		}
		else c+=l;
	}
	*d = 0;
}

int IdEstimateFormatSize(const char *String)
{
	int ret = 0;
	LONG l,id;
	const char *c,*r, *sc;

	for (c=String;*c;)
	{
		l = 1;
		if (*c=='$')
		{
			id = get_tag_id(c);
			if (id!=-1)
			{
				l = strlen(str_tags[id]);				
				r = IdHardware_ppc( id, NULL );
				if (r) ret+=strlen(r);
			}
		}

		if (l==1)
		{
			ret++; c++;
		}
		else c+=l;
	}

	return ret+1;
}


const char *str_tags[]={
		"$SYSTEM$",
		"$CPU$",
		"$FPU$",
		"$MMU$",
		"$OSVER$",
		"$EXECVER$",
		"$WBVER$",
		"$ROMSIZE$",
		"$CHIPSET$",
		"$GFXSYS$",
		"$CHIPRAM$",
		"$FASTRAM$",
		"$RAM$",
		"$SETPATCHVER$",
		"$AUDIOSYS$",
		"$OSNR$",
		"$VMMCHIPRAM$",
		"$VMMFASTRAM$",
		"$VMMRAM$",
		"$PLNCHIPRAM$",
		"$PLNFASTRAM$",
		"$PLNRAM$",
		"$VBR$",
		"$LASTALERT$",
		"$VBLANKFREQ$",
		"$POWERFREQ$",
		"$ECLOCK$",
		"$SLOWRAM$",
		"$GARY$",
		"$RAMSEY$",
		"$BATTCLOCK$",
		"$CHUNKYPLANAR$",
		"$POWERPC$",
		"$PPCCLOCK$",
		"$CPUREV$",
		"$CPUCLOCK$",
		"$FPUCLOCK$",
		"$RAMACCESS$",
		"$RAMWIDTH$",
		"$RAMCAS$",
		"$RAMBANDWIDTH$",
		"$TCPIP$",
		"$PPCOS$",
		"$AGNUS$",
		"$AGNUSMODE$",
		"$DENISE$",
		"$DENISEREV$",
		"$EMULATED$",
		"$XLVERSION$",
		"$HOSTOS$",
		"$HOSTVERS$",
		"$HOSTMACHINE$",
		"$HOSTCPU$",
		"$HOSTSPEED$",
		"$LASTALERTTASK$",
		"$PAULA$",
		"$ROMVER$",
		"$RTC$",
		NULL};


void IdExpansion_write_tags(struct PCIDevice *device, struct TagItem *Tags)
{
	struct TagItem *Tag;

	uint16 VendorID = device->ReadConfigWord(PCI_VENDOR_ID);
	uint16 DeviceID = device->ReadConfigWord(PCI_DEVICE_ID);


	for (Tag = Tags; Tag -> ti_Tag != TAG_DONE; Tag ++ )
	{
		switch (Tag -> ti_Tag)
		{

			case IDTAG_ManufStr:
					sprintf( (char *) Tag -> ti_Data, "%04x",VendorID );
					break;

			case IDTAG_ProdStr:
					sprintf( (char *) Tag -> ti_Data, "%04x",DeviceID );
					break;

			case IDTAG_ClassStr:
					sprintf( (char *) Tag -> ti_Data, "%s","PCI/PCIe/AGP" );
					break;

			case IDTAG_Secondary:
					*((ULONG *) (Tag -> ti_Data)) = 1;
					break;

			case IDTAG_ClassID:
					*((ULONG *) (Tag -> ti_Data)) = 1;
					break;

			case IDTAG_UnknownFlag:
					*((ULONG *) (Tag -> ti_Data)) = 1;
					break;

			case IDTAG_Delegate:
					*((ULONG *) (Tag -> ti_Data)) = 1;
					break;
		}
	}	
}

LONG IdExpansion(struct TagItem *Tags)
{
	struct PCIDevice *device = NULL;
	struct ConfigDev **cd = NULL;
	struct TagItem *Tag;
	ULONG Localize = 0;
	ULONG BufferLength = 30;

	for (Tag = Tags; Tag -> ti_Tag != TAG_DONE; Tag ++ )
	{
		switch (Tag -> ti_Tag)
		{
			case IDTAG_ConfigDev:
					printf("DTAG_ConfigDev\n"); break;

			case IDTAG_ManufID:
					printf("DTAG_ManufID\n");	break;

			case IDTAG_ProdID:
					printf("DTAG_ProdID\n"); break;

			case IDTAG_Expansion:
					printf("DTAG_Expansion\n");
					cd = (struct ConfigDev **) (Tag -> ti_Data); break;

			case IDTAG_Localize:
					Localize = Tag -> ti_Data;	break;

			case IDTAG_StrLength:
					BufferLength = Tag -> ti_Data;	break;					
		}
	}

	if (!cd)
	{
		printf("sorry can't do it\n");
		return IDERR_DONE;
	}

	if (!*cd) 
	{
		*cd = malloc(sizeof(struct ConfigDev));
		(*cd) -> cd_SlotAddr = 0;
	}
	else	(*cd) -> cd_SlotAddr ++;

	if (!*cd)
	{
		printf("sorry no mem\n");
		return IDERR_DONE;	// failed to alloc mem.
	}

	device = IPCI -> FindDeviceTags( FDT_Index, (*cd) -> cd_SlotAddr , TAG_END );
	if (device)
	{
		(*cd) -> cd_Rom.er_Manufacturer =  device->ReadConfigWord(PCI_VENDOR_ID);

		IdExpansion_write_tags(device,Tags);
		IPCI -> FreeDevice( device );
	}
	else 
	{
		free(*cd);	// we are done...
		*cd = NULL;
		return IDERR_DONE;
	}

	return 0;
}

