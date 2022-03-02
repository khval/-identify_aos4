
#include <stdlib.h>
#include <stdio.h>

#include <proto/dos.h>
#include <proto/exec.h>

#define CATCOMP_NUMBERS
#define CATCOMP_STRINGS
#define CATCOMP_ARRAY

#include "../locale/locale.c"

const char *NA = "<NULL>";

const char *get_locale_str(uint32 id)
{
	struct CatCompArrayType *i;

	for (i = CatCompArray; i -> cca_ID != END_OF_LIST; i++)
	{
		if ( i -> cca_ID == id )
		{
			return i -> cca_Str;
		}
	}

	return NA;
}


