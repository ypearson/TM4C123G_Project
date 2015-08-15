#!/bin/bash
set -x
source setupenv.source
make

if [ "$1" == "debug" ]; then
	arm-unknown-eabi-gdb code.elf -tui
fi

