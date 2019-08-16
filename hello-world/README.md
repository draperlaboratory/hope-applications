# Hello World

This is a basic hello world application that can be built with either the FreeRTOS or bare metal runtime.
The following instructions build the application with FreeRTOS, but they can be replicated for bare metal
by substituting `frtos` for `bare` in each command. This README assumes that a working HOPE development
environment is installed.

## Installing a runtime

Use the `isp_install_runtime` command to add runtime-specific to the application directory:

```
$ isp_install_runtime frtos
```

This command will copy the `isp-runtime-frtos` directory and the `isp-runtime-frtos.mk` Makefile into the
current working directory. `isp-runtime-frtos` contains runtime-specific code stubs to be compiled into the
application. `isp-runtime-frtos.mk` is used in combination with `common.mk` to form a Makefile to build the
application with runtime support.

## Building and running

Once the FreeRTOS runtime files are created, build the application with:

```
make -f Makefile.frtos
```

This should produce a RISC-V application named `hello`. To run this application, run:

```
make -f Makefile.frtos run
```

This command uses the `isp_run_app` script to launch the application in QEMU. UART output from the application
should appear on-screen, including a `Hello world!` message.
