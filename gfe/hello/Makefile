TARGET       := hello

C_SOURCES		 := hello.c
C_OBJECTS		 := $(patsubst %.c,%.o,$(C_SOURCES))

ASM_SOURCES  := boot.S
ASM_OBJECTS  := $(patsubst %.S,%.o,$(ASM_SOURCES))

OBJECTS      := $(C_OBJECTS) $(ASM_OBJECTS)

RUNTIME			 := frtos

UART				 := uart/
LIBUART			 := $(UART)/libuart.a

LIBS				 := $(LIBUART)

CFLAGS			 += -march=rv32ima -mabi=ilp32 -mcmodel=medium
CFLAGS			 += -Wall -Wextra -O0 -g3 -std=gnu11
CFLAGS			 += -ffunction-sections -fdata-sections -fno-builtin-printf

LDFLAGS			 := -T link.ld -nostartfiles -defsym=_STACK_SIZE=4K
LDFLAGS			 += -Wl,--wrap=isatty -Wl,--wrap=printf -Wl,--wrap=puts -Wl,--wrap=write
LDFLAGS			 += -luart -L$(UART)

INCLUDES		 := -I$(UART)
INCLUDES		 += -I$(ISP_PREFIX)/riscv32-unknown-elf/include

CC					 := $(ISP_PREFIX)/bin/clang

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS) $(LIBS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) $(OBJECTS) -o $@ $(LDFLAGS)

$(LIBUART):
	make -C $(UART)

$(C_OBJECTS): %.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $< -c -o $@

$(ASM_OBJECTS): %.o: %.S
	$(CC) $< -c -o $@

clean:
	rm -rf *.o $(TARGET)
	make -C $(UART) clean
