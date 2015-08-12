CROSS=arm-unknown-eabi-
CC=${CROSS}gcc
LD=${CROSS}ld
AS=${CROSS}as

TARGET=run
CFLAGS= -c -g -Wall -nostartfiles -mcpu=cortex-m4 -mthumb
AFLAGS= -c -g -mcpu=cortex-m4 -mthumb
LDFLAGS=

CSRC= main.c \
	pll.c

ASRC = startup.s \

COBJ=$(CSRC:.c=.o)
AOBJ=$(ASRC:.s=.o)

OBJ = $(COBJ) $(AOBJ)

all: clean $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.s
	$(AS) $(AFLAGS) $< -o $@

$(TARGET): $(OBJ)
	$(LD) -T ld.script $(LDFLAGS) $^ -o $@

clean:
	@rm -f *.o
	@rm -f $(TARGET)
