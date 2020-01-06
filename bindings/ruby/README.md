# ToolbitSDK Ruby Library

## Introduction

ToolbitSDK provide Ruby Library to communicate with a target device.

For example, to read voltage and current values from DMM, just make an object of Dmm class defined by tbi.so and use member functions as follows as:
```
require 'tbi'

dmm = Tbi::Dmm.new

puts sprintf("%.3f [V]", dmm.getVoltage())
puts sprintf("%.3f [mA]", 1000.0 * dmm.getCurrent())
```


## Build Ruby Library

### Windows

- MinGW and MSYS2 environment is needed
    - http://www.msys2.org/
- The following ruby is recommended
    - mingw-w64-x86_64-ruby
    - RubyInstaller for windows 32bit version
       - Ruby 2.4.1-1 (x86) is verified
       - 64bit version is not verified
- Install "MSYS2 and MINGW development toolchain"

Launch MSYS2 and install swig if you don't  have it
```
$ pacman -S swig
```

Clone ToolbitSDK by git or download it from GitHub
```
$ git clone https://github.com/toolbitorg/ToolbitSDK.git
```

Build Ruby library
```
$ cd ToolbitSDK/bindings/ruby
$ make
```

tbi.so is built and copied to ../samples. Now you can test it with DMM as follows
```
$ cd ../samples
$ ./dmm_test.rb
0.000 [V]
0.000 [mA]
```
