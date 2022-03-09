# identify_aos4

This is a replica project aimed at duplication same set of features as the AmigaOS3.x M68K version of this library (written by Richard "Shred" Koerber).

The big difference is that this is a PowerPC library and its written in C, the AmigaOS 3.x m68k version is written in old school assembler.
this is why I can't cooperate much to the original library. But I hope we can agree on some things like ID numbers and so on.
I also hope to reuse what ever I can, but put as little as possible into this repo. (too not duplicate work, unnecessary.)

# Why?

* Because its most safe why to query the system without poking the hardware.
* Because it’s useful to have common and standard API’s. 
* Because programs will not work without it.
* Because having a native version will allow people to use it in C programs.
* Becouse the 680x0 version crashes on AmigaONE and Sam440/460 systems.

# Limitations

value, but if someone wants to add support for this, please go right ahead.
There are some benchmarking stuff, not supported. (Will need to find a way to compile inn some 68k binary, and use hunk realloc code.)
I focused on AmigaONE and Sam’s, so it will report wrong info on Blizzard PPC (A1200) and Cyberstorm PPC (A4000), feel free to fix it.
Or use the MC680x0 version, should work on Classic Amiga systems.

# Different

IdExpansion will not repport zorro cards on AmigaONE/Sam4x0 systems, insted it lists PCI/PCIe/AGP cards.

# Bugs 

Please repport any bugs, or discrepancy you find (not listed).
While might not fix every issue, its useful to keep track of anything that needs to be done.

https://github.com/khval/identify_aos4/issues

# Contribute

Please do, ask for access to this repo. 

Need translations, tools or improvements, however let Richard "Shred" Koerber to define the standard for now.

https://github.com/shred/identify/issues

Best Regards

Kjetil Hvalstrand
