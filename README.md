# libs_edu_ciaa_bare

Proyecto de Eclipse para programar EDU-CIAA-NXP en modo baremetal (Basado en el repositorio de Martin Ribelotta y las librerías LPCOpen de NXP Semiconductors N.V.)

![CIAA logo](https://avatars0.githubusercontent.com/u/6998305?v=3&s=128)

## Dependencies

 - arm-none-eabi (https://launchpad.net/gcc-arm-embedded)
 - make and fileutils (rm, sed, echo, etc) from your system (linux,unix,cygwin,mingw)
 - openocd with ftdi driver support

## Usage
 - From command line type `make all` or simply `make`
 - With board connected, type `make download`. This deploys program to target board
 - In order to erase chip, type `make erase`
 - For debugging, in another console, type `make openocd`. This starts openocd which listens for gdb connections
 - In the main console type `make debug`. This start gdb and connects with openocd, deploys code to target's flash and starts execution

## Status

This is work in progress. Some examples do not work.

An updated status of complied pograms can be found in [the last recent build log](logs/test_build_all.log)

**WARNING**: If an example is succesfully compiled, not necessarily works when deployed

In order to update build log, type `make test_build_all` while in main directory
