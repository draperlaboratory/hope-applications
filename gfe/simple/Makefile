TARGET       := simple

C_SOURCES		 := simple.c
C_OBJECTS		 := $(patsubst %.c,%.o,$(C_SOURCES))

ASM_SOURCES  := boot.S
ASM_OBJECTS  := $(patsubst %.S,%.o,$(ASM_SOURCES))

OBJECTS      := $(C_OBJECTS) $(ASM_OBJECTS)

CFLAGS			 += -march=rv32i -mabi=ilp32 -mcmodel=medium
CFLAGS			 += -Wall -Wextra -O0 -g3 -std=gnu11
CFLAGS			 += -ffunction-sections -fdata-sections -fno-builtin-printf

LDFLAGS			 := -T link.ld -nostartfiles -defsym=_STACK_SIZE=4K

INCLUDES		 := -I$(ISP_PREFIX)/riscv32-unknown-elf/include

CC					 := $(ISP_PREFIX)/bin/clang

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS) $(LIBS) link.ld
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) $(OBJECTS) -o $@ $(LDFLAGS)

$(C_OBJECTS): %.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $< -c -o $@

$(ASM_OBJECTS): %.o: %.S
	$(CC) $< -c -o $@

clean:
	rm -rf *.o $(TARGET)
