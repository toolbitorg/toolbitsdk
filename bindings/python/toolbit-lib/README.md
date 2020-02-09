# Toolbit library for Python
[![PyPI version](https://badge.fury.io/py/toolbit-lib.svg)](https://badge.fury.io/py/toolbit-lib)

The target device of this library is **Toolbit DMM**, digital multimeter, that is used with PC to measure DC voltage or current.

The target version of this library is as follows:
  * Python: *3.6 or later*


# Installation

The toolbit-lib package is published to the PyPI repository. It can be installed by the following steps:

### Ubuntu linux / Raspberry Pi
```shell
  sudo apt install libudev-dev
  pip3 install toolbit-lib
```

### macOS
```shell
  pip3 install toolbit-lib
```

### Windows
```shell
  pip3 install toolbit-lib
```

# Usage

### Example

Connect your device to USB port and execute the following code:

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

Also, [sample code is available here](https://github.com/toolbitorg/ToolbitSDK/tree/master/bindings/python/samples).

# Build

Download the latest source from [GitHub repository](https://github.com/toolbitorg/ToolbitSDK).

The following command/software is required to build toolbit-lib:
  * make
    * For Windows, MinGW is highly recommended
  * swig: http://www.swig.org/
  * Ubuntu linux / Raspberry Pi
    * libudev-dev

### Ubuntu linux / macOS / Rasberry Pi
```shell
  cd bindings/python/toolbit-lib
  make
  sudo make install
```

### Windows
```shell
  cd bindings/python/toolbit-lib
  build.bat
  python setup.py install
```


# License

[GPLv2] Please refer to the LICENSE file in this repository
