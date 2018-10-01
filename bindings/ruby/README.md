# ToolbitSDK Ruby Library

## Introduction

ToolbitSDK provide Ruby Library to communicate with a target device.

For example, to read voltage and current values from Luke, just make an object of Luke class defined by tbi.so and use member functions as follows as:
```
require 'tbi'

luke = Tbi::Luke.new

puts sprintf("%.3f [V]", luke.getVoltage())
puts sprintf("%.3f [mA]", 1000.0 * luke.getCurrent())
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
$ cd ToolbitSDK/bindings/ruby/src
$ ./build.sh
```

tbi.so is built and copied to ../samples. Now you can test it with Luke as follows
```
$ cd ../samples
$ ./luke_test.rb
0.000 [V]
0.000 [mA]
```
