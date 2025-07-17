# BoinkOS Userland Program Template

Custom programs can be written in /src/main.c
It can be complied by running `make`. The makefile produces an elf file in /build/

While booting the operating system, make sure /path/to/program.elf is specified within the makefile to access it within the operating system if it isn't already specified.