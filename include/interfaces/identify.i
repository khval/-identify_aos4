#ifndef IDENTIFY_INTERFACE_DEF_H
#define IDENTIFY_INTERFACE_DEF_H
/*
** This file is machine generated from idltool
** Do not edit
*/ 

#include <exec/types.i>
#include <exec/exec.i>
#include <exec/interfaces.i>

STRUCTURE IdentifyIFace, InterfaceData_SIZE
	    FPTR IIdentify_Obtain
	    FPTR IIdentify_Release
	    FPTR IdentifyIFace_Expunge_UNIMPLEMENTED
	    FPTR IdentifyIFace_Clone_UNIMPLEMENTED
	    FPTR IIdentify_IdExpansion
	    FPTR IIdentify_IdHardware
	    FPTR IIdentify_IdAlert
	    FPTR IIdentify_IdFunction
	    FPTR IIdentify_IdHardwareNum
	    FPTR IIdentify_IdHardwareUpdate
	    FPTR IIdentify_IdFormatString
	    FPTR IIdentify_IdEstimateFormatSize
	LABEL IdentifyIFace_SIZE

#endif
