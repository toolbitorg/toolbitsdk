# Toolbit library for Electron
[![NPM version](https://badge.fury.io/js/toolbit-lib.svg)](https://badge.fury.io/js/toolbit-lib)

This library is prepared for [**ToolbitDMM**](https://github.com/toolbitorg/ToolbitDMM) that is cross platform application based on Electron to control a digital multimeter released by Toolbit.

The target version of the library is as follows:
  * electron: *4.2.12* only

It is very old but later version is not supported due to SWIG limitation. In addition, it is assumed that the library is built for only this version of Electron.

If you want to control a device by your code, please use [python library](https://github.com/toolbitorg/ToolbitSDK/tree/master/bindings/python/toolbit-lib) instead of this.


# Installation

The toolbit-lib package is published to the npm registry. It can be installed by the following steps:

### Ubuntu linux / Raspberry Pi
```shell
  sudo apt install libudev-dev
  npm install toolbit-lib
```

### macOS
```shell
  npm install toolbit-lib
```

### Windows
```shell
  npm install toolbit-lib
```


# Build

Download the latest source from [GitHub repository](https://github.com/toolbitorg/ToolbitSDK).

The following command/software is required to build toolbit-lib:
  * make
  * node-gyp
  * swig: http://www.swig.org/
  * Ubuntu linux / Raspberry Pi
    * libudev-dev

Build it by make command:
```shell
  cd bindings/electron
  make
```
Library for electron will be created and copied to toolbit-lib/lib folder


# License

[GPLv2] Please refer to the LICENSE file in this repository
