CC=/home/ypearson/x-tools/x86_64-unknown-linux-gnu/bin/x86_64-unknown-linux-gnu-gcc
TARGET=run
CFLAGS= -c -g -O0
LDFLAGS=


SRC= cfifo.c \
	main.c

OBJ=$(SRC:.c=.o)

all: clean $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	@rm -f *.o
	@rm -f $(TARGET)
