
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <proto/exec.h>
#include <proto/dos.h>
#include <utility/tagitem.h>
#include <libraries/identify.h>

#define __USE_INLINE__

#include <proto/version.h>

#include "tools.h"

char osver[30];
char wbver[30];
char ppc_clock_str[30];
const char *str_na = "N/A";
const char *str_true = "TRUE";
const char *str_false = "FALSE";
const char *str_none = "NONE";
const char *str_yes = "YES";
const char *str_no = "NO";

extern const char *get_locale_str(uint32 id);


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

const char *get_str(ULONG type, ULONG id)
{
	const char *ret = str_na;

	switch (type)
	{
		case IDHW_SYSTEM:
			ret=get_locale_str(4500+id);	break;

		case IDHW_CPU:
			ret=get_locale_str(5000+id);	break;

		case IDHW_FPU:
			ret=id ? get_locale_str(5008+id) : str_none;
			break;

		case IDHW_MMU:
			ret=id ? str_yes : str_no;	break;

		case IDHW_POWERPC:
			ret=get_locale_str(7000+id);	break;

		case IDHW_POWERFREQ:
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

		case IDHW_OSVER:
			get_osver();
			ret = osver;
			break;

		case IDHW_WBVER:
			get_wbver();
			ret = wbver;
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

	printf("Buffer %08x, %08x BufferLength %d\n",Buffer,BufferE,BufferLength);

	d = Buffer;
	for (c=String;*c;)
	{
		l = 1; r = 1;

		printf("%c\n",*c);

		if (*c=='$')
		{
			id = get_tag_id(c);

			printf("ID: %d\n",id);

			if (id!=-1)
			{
				printf("Found\n");

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

	printf("%08x\n",d);
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

