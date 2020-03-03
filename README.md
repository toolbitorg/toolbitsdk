# Toolbit SDK

# Overview

Toolbit SDK is Software Develepment Kit for measurement and automation system. It is prepared for a multimeter named as **Toolbit DMM** for now. Please see the following project page: https://hackaday.io/project/10398-luke-open-framework-multimeterlogger

The target platform of SDK is as follows:
  * Ubuntu Linux
  * macOS
  * Windows
  * Raspberry Pi

Source code is described by C/C++ but libraries for the following languages have been released by using SWIG:
  * [**Python 3.6 or later**](bindings/python/toolbit-lib/README.md): [![PyPI version](https://badge.fury.io/py/toolbit-lib.svg)](https://badge.fury.io/py/toolbit-lib)
  * [**Node.js specially for Electron**](bindings/electron/README.md): [![NPM version](https://badge.fury.io/js/toolbit-lib.svg)](https://badge.fury.io/js/toolbit-lib)


# Quickstart

### Python

Install [Python toolbit-lib package](https://badge.fury.io/py/toolbit-lib) by pip command.

```shell
  pip3 install toolbit-lib
```

In case of linux, you might be required to install libudev-dev in advance and then to execute pip with `sudo` command. Please see [here](bindings/python/toolbit-lib/README.md) in details.

For example, you can get voltage/current measurement result from a connected device as follows:
```python
  from toolbit import Dmm

  dmm = Dmm()
  dmm.open()
  print(str('%03.3f' % dmm.getVoltage()) + " [V]")
  print(str('%03.3f' % (1000.0 * dmm.getCurrent())) + " [mA]")
```

Toolbit SDK uses object-oriented programming.
  * `dmm` instance is created by using `Dmm()` constructor
  * `dmm.open()` method opens a target device
  * `dmm.getVotage()` and `dmm.getCurrent()` methods return measurement values

Result will be shown as follows:
```shell
  0.003 [V]
  0.000 [mA]
```

# Guide

### Electron

[Node.js library for Electron](bindings/electron/README.md) is prepared to build cross-platform desktop apps. It is used by [Toolbit DMM GUI application](https://github.com/toolbitorg/ToolbitDMM).


# Build

Download the latest source from [GitHub repository](https://github.com/toolbitorg/ToolbitSDK).

The following command/software is required to build library:
  * make
    * For Windows, MinGW is highly recommended
  * Ubuntu linux / Raspberry Pi
    * libudev-dev

Library for C++ is built by the following steps:
```shell
  cd src
  make
```
Object and library files are created in *ToolbitSDK/build* and *ToolbitSDK/lib* folders.


If you want to build other language bindings, please refer to the following pages:
* [Python](bindings/python/toolbit-lib/README.md)
* [Electron](bindings/electron/README.md)


# Dependency
  * https://github.com/signal11/hidapi
    * This repository contains this library as it is
    * Please see README.txt and LICENSE.txt in [src/HIDAPI](src/HIDAPI)


# License

[GPLv2] Please refer to the [LICENSE](LICENSE) file in this repository
