BASE_DIR = $(abspath .)

CC     = $(ISP_PREFIX)/bin/clang
CFLAGS += -O0 -g3 -Wall -mabi=ilp32 -march=rv32ima

CFLAGS += -DALIGN_UART -DFPGA_GFE

BUILD_DIR  = $(BASE_DIR)/build
LIB_TARGET = $(BUILD_DIR)/libuart.a

CFLAGS += -I$(ISP_PREFIX)/include \
          -I$(BASE_DIR) \
          -ffunction-sections \
          -fno-builtin-printf

SRCS   = $(wildcard *.c)
OBJS   = $(SRCS:%=$(BUILD_DIR)/%.o)

all: $(LIB_TARGET)
.PHONY: all clean
.PRECIOUS: $(BUILD_DIR)/ $(BUILD_DIR)%/
.SECONDEXPANSION:

$(BUILD_DIR)/:
	mkdir -p $@

$(BUILD_DIR)/%.c.o: %.c | $$(@D)/
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

$(LIB_TARGET): $(OBJS)
	ar rcs $@ $(OBJS)

clean:
	rm -rf $(BUILD_DIR)
