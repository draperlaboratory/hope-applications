TARGET       := code_write_fails_simple

C_SOURCES		 := code_write_fails.c
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

OUTPUT_DIR   := ../output

.PHONY: all clean

all: $(OUTPUT_DIR)/$(TARGET)

$(OUTPUT_DIR)/$(TARGET): $(TARGET)
	cp -f $(TARGET) $(OUTPUT_DIR)

$(TARGET): $(OBJECTS) $(LIBS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) $(OBJECTS) -o $@ $(LDFLAGS)

$(C_OBJECTS): %.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $< -c -o $@

$(ASM_OBJECTS): %.o: %.S
	$(CC) $< -c -o $@

clean:
	rm -rf *.o $(TARGET)
