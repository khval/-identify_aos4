#ifndef PROTO_IDENTIFY_H
#define PROTO_IDENTIFY_H

/*
**	$Id$
**
**	Prototype/inline/pragma header file combo
**
**	Copyright (c) 2010 Hyperion Entertainment CVBA.
**	All Rights Reserved.
*/

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef LIBRARIES_IDENTIFY_H
#include <libraries/identify.h>
#endif

/****************************************************************************/

#ifndef __NOLIBBASE__
 #if defined(__cplusplus) && defined(__USE_AMIGAOS_NAMESPACE__)
  extern struct AmigaOS::Library * IdentifyBase;
 #else
  extern struct Library * IdentifyBase;
 #endif
#endif /* __NOLIBBASE__ */

/****************************************************************************/

#ifdef __amigaos4__
 #include <interfaces/identify.h>
 #ifdef __USE_INLINE__
  #include <inline4/identify.h>
 #endif /* __USE_INLINE__ */
 #ifndef CLIB_IDENTIFY_PROTOS_H
  #define CLIB_IDENTIFY_PROTOS_H 1
 #endif /* CLIB_IDENTIFY_PROTOS_H */
 #ifndef __NOGLOBALIFACE__
  #if defined(__cplusplus) && defined(__USE_AMIGAOS_NAMESPACE__)
   extern struct AmigaOS::IdentifyIFace * IdentifyIFace;
  #else
   extern struct IdentifyIFace * IdentifyIFace;
  #endif
 #endif /* __NOGLOBALIFACE__ */
#else /* __amigaos4__ */
 #ifndef CLIB_IDENTIFY_PROTOS_H
  #include <clib/identify_protos.h>
 #endif /* CLIB_IDENTIFY_PROTOS_H */
 #if defined(__GNUC__)
  #ifndef __PPC__
   #include <inline/identify.h>
  #else /* __PPC__ */
   #include <ppcinline/identify.h>
  #endif /* __PPC__ */
 #elif defined(__VBCC__)
  #ifndef __PPC__
   #include <inline/identify_protos.h>
  #endif /* __PPC__ */
 #else /* __GNUC__ */
  #include <pragmas/identify_pragmas.h>
 #endif /* __GNUC__ */
#endif /* __amigaos4__ */

/****************************************************************************/

#endif /* PROTO_IDENTIFY_H */
