VERSION		EQU	53
REVISION	EQU	1

DATE	MACRO
		dc.b '22.2.2022'
		ENDM

VERS	MACRO
		dc.b 'identify.library 53.1'
		ENDM

VSTRING	MACRO
		dc.b 'identify.library 53.1 (22.2.2022)',13,10,0
		ENDM

VERSTAG	MACRO
		dc.b 0,'$VER: identify.library 53.1 (22.2.2022)',0
		ENDM
