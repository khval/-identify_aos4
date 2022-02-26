VERSION = 53
REVISION = 1

.macro DATE
.ascii "22.2.2022"
.endm

.macro VERS
.ascii "identify.library 53.1"
.endm

.macro VSTRING
.ascii "identify.library 53.1 (22.2.2022)"
.byte 13,10,0
.endm

.macro VERSTAG
.byte 0
.ascii "$VER: identify.library 53.1 (22.2.2022)"
.byte 0
.endm
