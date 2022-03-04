
#define __USE_INLINE__

#include <stdio.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/version.h>
#include <utility/tagitem.h>
#include <libraries/identify.h>

#include "tools.h"

extern char osver[30];
extern char wbver[30];
extern char ppc_clock_str[30];

extern const char *str_tags[];

const char *IdHardware_ppc(ULONG type, struct TagItem *TagList);

LONG get_tag_id(const char *tag)
{
	ULONG ret = 0;
	const char **i;

	for (i=str_tags;*i;i++)
	{
		if (strncmp(tag,*i,strlen(*i))==0) return i-str_tags;
	}

	return -1;
}

ULONG get_osver()
{
	unsigned int major,minor;
	int32 len = GetVar("kickstart",osver,sizeof(osver),GVF_GLOBAL_ONLY);
	if (len) sscanf(osver,"%u.%u\n",&major,&minor);
	return (minor << 16) | major;
}

ULONG get_wbver()
{
	unsigned int major,minor;
	int32 len = GetVar("workbench",wbver,sizeof(wbver),GVF_GLOBAL_ONLY);
	if (len) sscanf(wbver,"%u.%u\n",&major,&minor);
	return (minor << 16) | major;
}

ULONG get_powerpc_clock()
{
	uint64 frequency;
	GetCPUInfoTags( GCIT_ProcessorSpeed, &frequency, TAG_DONE);
	return (ULONG) (frequency);
}

void get_powerpc_clock_str()
{
	uint32 unit = 0;
	uint64 frequency;
	double f;
	const char *array[]={"Hz","KHz","Mhz","GHz","THz",NULL};

	GetCPUInfoTags( GCIT_ProcessorSpeed, &frequency, TAG_DONE);

	f = (double) frequency;

	while (frequency>1000)
	{
		f/=1000.0f;
		frequency/=1000;
		unit++;
	}

	sprintf(ppc_clock_str,"%0.2f %s",f,array[unit]);

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
			return (model - CPUTYPE_PPC750CXE) + IDPPC_750CXE -1;
	}
	return 0;
}



