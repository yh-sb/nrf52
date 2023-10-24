# nRF52 submodule of [mcu-framework](https://github.com/yhsb2k/mcu-framework)

[![build](https://github.com/yhsb2k/nrf52/workflows/build/badge.svg)](https://github.com/yhsb2k/nrf52/actions?workflow=build)
[![license](https://img.shields.io/github/license/yhsb2k/nrf52?color=blue)](https://github.com/yhsb2k/nrf52/blob/master/LICENSE)

## How to build
```bash
git clone --recursive https://github.com/yhsb2k/nrf52.git
cd nrf52
# Install python dependencies:
# python -m pip install --upgrade pip
# python -m pip install -r third_party/zephyr/scripts/requirements.txt
make
```
**Other targets:**
* `make flash` - Upload firmware to the target
* `make erase` - Erase all memory on the target
* `make reset` - Reset the target
* Debug is available in VSCode **or** using `make debug` target to start GDB server

## Requirements
* [GNU Arm Embedded Toolchain](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)
* [CMake](https://cmake.org/download)
* [Ninja](https://ninja-build.org)
* [Make](https://winlibs.com)
* [Python](https://www.python.org/downloads)
* [JLink](https://www.segger.com/downloads/jlink)
