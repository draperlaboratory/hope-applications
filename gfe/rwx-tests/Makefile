.PHONY: all
.PHONY: runtime
.PHONY: clean

TEST_DIRS				:= simple
TEST_DIRS				+= code_write_fails_simple
TEST_DIRS				+= data_exe_fails_simple
TEST_DIRS				+= echo
TEST_DIRS				+= hello
TEST_DIRS				+= code_write_fails
TEST_DIRS				+= data_exe_fails

OUTPUT					:= output
RUNTIME_DIR			:= runtime
TESTS						:= $(patsubst %,$(OUTPUT)/%,$(TEST_DIRS))
RUNTIME					:= $(patsubst %,$(RUNTIME_DIR)/isp-run-%-rwx,$(TEST_DIRS))
TAG_HEX					:= $(patsubst %,%/Mem.hex,$(RUNTIME))

HOPE_SRC				:= $(HOME)/hope-src

all: $(TESTS)

runtime: $(RUNTIME)

$(RUNTIME_DIR)/isp-run-%-rwx: $(OUTPUT)/%
	isp_run_app $< -s vcs -r frtos -p rwx -o $(RUNTIME_DIR) -d \
		--soc $(HOPE_SRC)/policy-engine/soc_cfg/gfe-vcu118.yml

$(OUTPUT)/%: %
	mkdir -p $(OUTPUT)
	make -C $<

clean-test-dirs: $(TEST_DIRS)
	make -C $< clean

clean: clean-test-dirs
	rm -rf $(OUTPUT)
	rm -rf $(RUNTIME_DIR)
	make -C uart clean
