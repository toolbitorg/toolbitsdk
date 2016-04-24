ToolbitSDK
====

ToolbitSDK is Softare Develepment Kit for measurement and automation system. Target device is a multimeter named as Luke for now. Please see the following project page: https://hackaday.io/project/10398-luke-open-framework-multimeterlogger

Measurement is fundamental to make or hack something. Let's work together to make it as open source!!

## Description

This is not ready for release. The status of the project is as follows as:

Done
- Prepare makefiles for gcc/MinGW/OSX and project file of VS2015
  - This is key for cross platform development
- Make hidcomm library
- Establisth USB communication between PC and Luke using HID API
  - HID API is awesome library released by Signal 11 software

To do list
- Define APIs of hidcomm library and implement it
- Make command line tool chain
- Make GUI application
- Support Android

## Reference

- http://www.signal11.us/oss/hidapi/

## Licence

[GPLv2] Please refer to the LICENSE file in this repository

