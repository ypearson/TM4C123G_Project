#!/bin/bash
set -x
source setupenv.source
TARGET=code.elf
if [ ! -d openocd ]; then
  ./getOpenOCD.sh
fi

if [ "$1" == "debug" ]; then
 make && (pkill openocd; \
  (openocd --file openocd/share/openocd/scripts/board/ek-tm4c123gxl.cfg > /dev/null 2>&1 &) \
  && arm-none-eabi-gdb -tui $TARGET )
else
 make
fi

