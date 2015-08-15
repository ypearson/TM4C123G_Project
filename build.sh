#!/bin/bash
set -x
source setupenv.source

if [ "$1" == "debug" ]; then
	make && arm-unknown-eabi-gdb code.elf -tui
else
	make
fi

