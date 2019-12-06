!#/bin/bash

set -e 

# this is where we will create the app
APP_BASE=$HOME/tmpdir
APP_NAME=main_blinky.elf
POL_NAME=rwx

# compile the kernel first
cd $HOME/pex-kernel
git checkout master
FPGA=gfe-sim DEBUG=1 make

# create the main_blinky app; how one creates an app is
# very much application dependent
# the next is building the APP_NAME - this is specific to the app
cd $HOME/hope-src/FreeRTOS/FreeRTOS/Demo/RISC-V_Galois_P1
## alternatively, the hope-gfe/FreeRTOS-mirror is also a good target branch
git checkout gfe-pipe 
make clean
PROG=main_blinky make


## create an isp-run-${APP_NAME}-${POL_NAME} dir with
## all the required hex files
cd $APP_BASE
isp_run_app $HOME/hope-src/FreeRTOS/FreeRTOS/Demo/RISC-V_Galois_P1/${APP_NAME} -s fpga -r frtos -p ${POL_NAME} -d --soc $HOME/hope-src/policy-engine/soc_cfg/gfe-vcu118.yml -e " --pex-kernel" $HOME/pex-kernel/build/kernel " --dump-hex" " --init-only"


## create a mem image of tags that can be preloaded in the kernel memory
cd $HOME/pex-kernel/tag_mem_hexdump
## the below shall create a Mem.hex file
./tag_mem_hexdump $APP_BASE/isp-run-${APP_NAME}-${POL_NAME}/bininfo/${APP_NAME}.taginfo Mem.hex

## create a VSIM simulation executable for the hardware
## make sure you check out the right submodules and right branches
cd $HOME/hope-gfe-silviu/chisel_processors/rocket-chip/vsim
git checkout ssith-p2-cg
## update the submodules
git submodule update --init --recursive
git pull
## make sure that the pipe-hw and dover-riscy are on the right branches
cd ../src/main/resources/vsrc/Pipe/pipe-hw
git checkout pipe-rocket-integ
git pull
cd ../dover-riscy
git checkout pipe
git pull
cd ../software
git checkout ssith-p2-cg
cd $HOME/hope-gfe-silviu/chisel_processors/rocket-chip/vsim
make clean;

## the below actually creates an executable simulation
make CONFIG=P1SimCGConfig PROJECT=galois.system debug

## place the application elf file in a known dir
mkdir -p output
cd output
## link the application into the output file - the location of the app elf file will be app-specific
ln -sF $HOME/hope-src/FreeRTOS/FreeRTOS/Demo/RISC-V_Galois_P1/${APP_NAME} ${APP_NAME}
cd ../

## simulate
## note that the DRAM_BASE in the fesv lib should point to the
## location of the AP base memory (0xC000_0000 in the GFE case)
## if your riscv-tool are not up to date, the application will not
## be loaded.

time ./simv-galois.system-P1SimCGConfig-debug +permissive –reportstats -q +ntb_random_seed_automatic +permissive-off +permissive +verbose +vcdplusfile=output/main_blinky.vpd +max-cycles=300000000 +cg_taginfo_file=${APP_BASE}/isp-run-${APP_NAME}-${POL_NAME}/${APP_NAME}.load_image.hex +cg_mem_file=${APP_BASE}/isp-run-${APP_NAME}-${POL_NAME}/pex.load_image.hex +tags_preload_file=$HOME/pex-kernel/tag_mem_hexdump/Mem.hex +permissive-off output/${APP_NAME} 2> output/${APP_NAME}.out
