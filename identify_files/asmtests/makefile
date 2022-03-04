# asm one don't work on AmigaOS4, we need to use VBCC (vasm)

compiler=c/vasmm68k_mot

options=-m68020 

link=c/vlink

enable=.enable
disable=.disable

include makefile.cfg

inc=-Isdk31: -Isdk31:includes/include_i

tests = IdHardwareNum.exe	IdHardware.exe		IdFormatString.exe

all:	${tests} 

clean:
		delete obj/#? #?.exe 

# compile tests

IdHardwareNum.exe: IdHardwareNum.s
		$(compiler) $(options) $(inc) -Fhunk -o obj/IdHardwareNum.o IdHardwareNum.s 
		$(link) -bamigahunk -o IdHardwareNum.exe -s  obj/IdHardwareNum.o

IdHardware.exe: IdHardware.s
		$(compiler) $(options) $(inc) -Fhunk -o obj/IdHardware.o IdHardware.s 
		$(link) -bamigahunk -o IdHardware.exe -s  obj/IdHardware.o

IdFormatString.exe: IdFormatString.s
		$(compiler) $(options) $(inc) -Fhunk -o obj/IdFormatString.o IdFormatString.s 
		$(link) -bamigahunk -o IdFormatString.exe -s  obj/IdFormatString.o

probe.exe: probe.s
		$(compiler) $(options) $(inc) -Fhunk -o obj/probe.o probe.s 
		$(link) -bamigahunk -o probe.exe -s  obj/probe.o

bitchg.exe: bitchg.s
		$(compiler) $(options) $(inc) -Fhunk -o obj/bitchg.o bitchg.s 
		$(link) -bamigahunk -o bitchg.exe -s  obj/bitchg.o

paulatest.exe: paulatest.s
		$(compiler) $(options) $(inc) -Fhunk -o obj/paulatest.o paulatest.s 
		$(link) -bamigahunk -o paulatest.exe -s  obj/paulatest.o

.PRECIOUS: %.hunk 

