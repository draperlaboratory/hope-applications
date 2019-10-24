TEST_DIRS				:= simple
TEST_DIRS				+= code_write_fails_simple
TEST_DIRS				+= data_exe_fails_simple
TEST_DIRS				+= hello
TEST_DIRS				+= code_write_fails
TEST_DIRS				+= data_exe_fails

OUTPUT					:= output
RUNTIME_DIR			:= runtime
TESTS						:= $(patsubst %,$(OUTPUT)/%,$(TEST_DIRS))
RUNTIME					:= $(patsubst %,$(RUNTIME_DIR)/isp-run-%-rwx,$(TEST_DIRS))
TAG_HEX					:= $(patsubst %,%/Mem.hex,$(RUNTIME))

HOPE_SRC				:= $(HOME)/hope-src
PEX_KERNEL_DIR  := $(HOME)/pex-kernel
PEX_KERNEL  		:= $(PEX_KERNEL_DIR)/build/kernel
TAG_MEM_HEXDUMP := $(PEX_KERNEL_DIR)/tag_mem_hexdump/tag_mem_hexdump

all: $(TESTS) $(RUNTIME) $(TAG_HEX)

%/Mem.hex: %
	$(TAG_MEM_HEXDUMP) $</bininfo/*.taginfo $@

$(RUNTIME_DIR)/isp-run-%-rwx: $(OUTPUT)/%
	isp_run_app $< -s fpga -r frtos -p rwx -o $(RUNTIME_DIR) -d \
		--soc $(HOPE_SRC)/policy-engine/soc_cfg/gfe-vcu118.yml \
		-e +pex-kernel $(PEX_KERNEL) +dump-hex +init-only

$(OUTPUT)/%: %
	mkdir -p $(OUTPUT)
	make -C $<

clean-test-dirs: $(TEST_DIRS)
	make -C $< clean

clean: clean-test-dirs
	rm -rf $(OUTPUT)
	rm -rf $(RUNTIME_DIR)
	make -C uart clean
