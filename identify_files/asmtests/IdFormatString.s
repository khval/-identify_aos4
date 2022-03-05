
	include "lvo/exec_lib.i"
	include "lvo/dos_lib.i"

	include "//reference/identify_lib.i"
	include "//reference/libraries/identify.i"

	SECTION main,CODE

OPENLIB	macro 
	lea \1Name,A1
	move.l 4.w,a6
	moveq #0,d0
	jsr _LVOOpenLibrary(a6)
	move.l d0,\1Base
	tst.l	d0
	beq	closeLibs
	endm

CLOSELIB	macro
	move.l \1Base(pc),a1
	jsr	closeLib
	endm

INFOTXT	macro
	move.l	#PRINT_FMT,D1	; FMT
	move.l	#printf_args,A1	; ARGS
	move.l	#txt\1,(A1)
	move.l	A1,D2			; D2
	move.l	a6,-(sp)
	move.l	dosBase,a6		; DosBase
	jsr		_LVOVPrintf(a6)	; Printf
	move.l	(sp)+,a6
	endm

INFOVALUE	macro
	move.l	#printf_args,A1	; ARGS
	move.l	\1,(A1)
	move.l	#PRINT_VALUE_FMT,D1	; FMT
	move.l	#printf_args,D2		; ARG ARRAY
	move.l	a6,-(sp)
	move.l	dosBase,a6		; DosBase
	jsr		_LVOVPrintf(a6)	; Printf
	move.l	(sp)+,a6
	endm

PRINTINFO	macro
	move.l	#printf_args,A1	; ARGS
	move.l	\2,(A1)
	move.l	#PRINT_\1_FMT,D1	; FMT
	move.l	#printf_args,D2		; ARG ARRAY
	move.l	a6,-(sp)
	move.l	dosBase,a6		; DosBase
	jsr		_LVOVPrintf(a6)	; Printf
	move.l	(sp)+,a6
	endm

DELAY	macro
	move.l #\1,d1
	jsr delay
	endm

writeText	macro
		lea 1\(pc),a1
		jsr _writeText
		endm

IdHardwareNum macro
		move.l \1,D0
		move.l \2,A0
		JSR _LVOIdHardwareNum(a6)
		endm

IdFormatString macro
		move.l \1,A0
		move.l \2,A1
		move.l \3,D0
		move.l \4,A2
		JSR _LVOIdFormatString(a6)
		endm

main:
	OPENLIB	dos
	OPENLIB	identify

	INFOTXT LibsOpen

	move.l	identifyBase,D0
	TST.l D0
	BEQ	.not_open
	move.l	D0,A6
	JSR _LVOIdHardwareUpdate(a6)
	INFOVALUE D0

	move.l #buffer,A0
	move.b	#'A',(A0)++
	move.b	#'m',(A0)++
	move.b	#'i',(A0)++
	move.b	#'g',(A0)++
	move.b	#'a',(A0)++
	move.b	#0,(A0)

	IdFormatString #hardware_fmt,#buffer,#128,#$0
	move.l #buffer,D0
	PRINTINFO TXT, D0

.not_open

closeLibs:
	CLOSELIB	identify
	CLOSELIB	dos
	rts

closeLib
	move.l a1,d0
	tst.l d0
	beq.s	.notOpen
	move.l 4,a6
	jsr	_LVOCloseLibrary(a6)
	moveq #0,d0
.notOpen
	rts

delay
	move.l dosBase(pc),a6
	jsr _LVODelay(a6)
	rts

_writeText:
	move.l (a1),d2
	add.l #4,a1
	move.l a1,d1
	move.l	dosBase(pc),A6
	jsr		_LVOWriteChars(a6)
	rts

dosBase:
	dc.l	0

identifyBase
	dc.l 0

printf_args:
		ds.l	20

txtLibsOpen:
	dc.b "Libs are open",$A,0

dosName:
	dc.b	"dos.library",0

identifyName:
	dc.b	"identify.library",0

PRINT_FMT
		dc.b	"%s",10,0

PRINT_TXT_FMT
		dc.b	"TXT: %s",10,0

PRINT_VALUE_FMT
		dc.b	"VALUE: %08lx",10,0

hello
		dc.b "hello",0

hardware_fmt
		dc.b "CPU: $CPU$ FPU: $FPU$ PPCOS: $PPCOS$, POWERPC: $POWERPC$ CLOCK: $PPCCLOCK$ SYSTEM: $SYSTEM$",10,0

buffer:
		ds.b	128
