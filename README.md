# ToolbitSDK

ToolbitSDK is Software Develepment Kit for measurement and automation system. Target device is a multimeter named as **Toolbit DMM** for now. Please see the following project page: https://hackaday.io/project/10398-luke-open-framework-multimeterlogger

The target platform of SDK is as follows:
  * Ubuntu Linux
  * macOS
  * Windows
  * Raspberry Pi

Source code is described by C/C++ but libraries for the following languages have been released by using SWIG:
  * [**Python 3.5 or later**](bindings/python/toolbit-lib/README.md): [![PyPI version](https://badge.fury.io/py/toolbit-lib.svg)](https://badge.fury.io/py/toolbit-lib)
  * [**JavaScript specially for Electron**](bindings/electron/README.md): [![NPM version](https://badge.fury.io/js/toolbit-lib.svg)](https://badge.fury.io/js/toolbit-lib)

# Usage

### Python

For example, you can get voltage/current measurement result from a connected device by using [Python library](bindings/python/toolbit-lib/README.md) as follows:
```python
  from toolbit import Dmm

  dmm = Dmm()
  dmm.open()
  print(str('%03.3f' % dmm.getVoltage()) + " [V]")
  print(str('%03.3f' % (1000.0 * dmm.getCurrent())) + " [mA]")
```

Result will be shown as follows:
```shell
  1.500 [V]
  0.000 [mA]
```

### Electron

[JavaScript library for Electron](bindings/electron/README.md) is prepared to build cross-platform desktop apps. It is used by [**ToolbitDMM**](https://github.com/toolbitorg/ToolbitDMM) GUI application.


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


# Reference
  * http://www.signal11.us/oss/hidapi/


# License

[GPLv2] Please refer to the LICENSE file in this repository
