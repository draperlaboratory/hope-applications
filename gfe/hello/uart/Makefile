BASE_DIR = $(abspath .)

CC     = $(ISP_PREFIX)/bin/clang
CFLAGS += -O0 -g3 -Wall -mabi=ilp32 -march=rv32ima

CFLAGS += -DALIGN_UART -DFPGA_GFE

LIB_TARGET = libuart.a

CFLAGS += -I$(ISP_PREFIX)/include \
          -I$(BASE_DIR) \
          -I$(BASE_DIR)/xilinx/common \
          -I$(BASE_DIR)/xilinx/uartns550 \
          -ffunction-sections \
          -fno-builtin-printf

SRCS   = uart.c \
				 wrap_isatty.c \
				 wrap_printf.c \
				 wrap_puts.c \
				 wrap_write.c \
			   xilinx/common/xbasic_types.c \
				 xilinx/common/xil_io.c \
				 xilinx/common/xil_assert.c \
				 xilinx/uartns550/xuartns550.c \
				 xilinx/uartns550/xuartns550_g.c \
				 xilinx/uartns550/xuartns550_format.c \
				 xilinx/uartns550/xuartns550_intr.c \
				 xilinx/uartns550/xuartns550_l.c \
				 xilinx/uartns550/xuartns550_options.c \
				 xilinx/uartns550/xuartns550_selftest.c \
				 xilinx/uartns550/xuartns550_sinit.c \
				 xilinx/uartns550/xuartns550_stats.c

OBJS   = $(patsubst %.c,%.o,$(SRCS))

all: $(LIB_TARGET)
.PHONY: all clean
.PRECIOUS: $(BUILD_DIR)/ $(BUILD_DIR)%/
.SECONDEXPANSION:

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

$(LIB_TARGET): $(OBJS)
	ar rcs $@ $(OBJS)

clean:
	rm -rf $(OBJS) $(LIB_TARGET)
