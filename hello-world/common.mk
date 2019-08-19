TARGET := hello
SOURCES := hello.c
OBJECTS := $(patsubst %.c,%.o,$(SOURCES))

CFLAGS += $(ISP_CFLAGS)
LDFLAGS += $(ISP_LDFLAGS)
INCLUDES += $(ISP_INCLUDES)

RUN_DIR := isp-run-$(TARGET)*

POLICY ?= none

.PHONY: all clean run-frtos run-bare

all: $(TARGET)

run:
	isp_run_app $(TARGET) -p $(POLICY) -s qemu -r $(RUNTIME) -u

sel4-lib:
	$(CC) -c $(SOURCES) -Iisp-runtime-sel4
	$(RISCV_AR) rcs target.a $(OBJECTS) 
	$(info done with sel4-lib)

$(TARGET): $(OBJECTS) $(ISP_OBJECTS) $(ISP_LIBS) $(ISP_DEPS)
	$(CC) $(CFLAGS) $(ISP_INCLUDES) \
									$(ISP_LIBS) \
									$(ISP_OBJECTS) \
									hello.c -o $@ $(ISP_LDFLAGS)

$(OBJECTS): %.o: %.c
	$(CC) $(CFLAGS) $(ISP_INCLUDES) $< -c -o $@

clean:
	rm -rf *.o $(TARGET) $(ISP_CLEAN) $(RUN_DIR)

clean-runtime:
	rm -rf isp-runtime-$(RUNTIME)*
