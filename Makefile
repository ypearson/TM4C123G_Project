CROSS=arm-none-eabi-
CC=${CROSS}gcc
LD=${CROSS}ld
AS=${CROSS}as

TARGET=code.elf
CFLAGS= -c -g -Wall -nostartfiles -mcpu=cortex-m4 -mthumb
AFLAGS= -c -g -mcpu=cortex-m4 -mthumb
LDFLAGS=

SRCFOLDER=src

CSRC=main.c \
	 pll.c \
	 systick.c \
	 uart.c \
     i2c.c \
     gpio.c \
     hih6130.c \
     cfifo.c \
     ascii_helpers.c \
     

CSRC:=$(addprefix $(SRCFOLDER)/, $(CSRC))

ASRC = src/startup.s

COBJ=$(CSRC:.c=.o)
AOBJ=$(ASRC:.s=.o)

OBJ = $(COBJ) $(AOBJ)

all: clean $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.s
	$(AS) $(AFLAGS) $< -o $@

$(TARGET): $(OBJ)
	$(LD) -T $(SRCFOLDER)/ld.script $(LDFLAGS) $^ -o $@

clean:
	@rm -f $(SRCFOLDER)/*.o
	@rm -f $(TARGET)
