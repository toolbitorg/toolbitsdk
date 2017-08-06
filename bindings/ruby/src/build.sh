#!/bin/bash

rm -fr *.h *.cpp *.so *.o *.cxx *.c
cp ../../../include/* ./
cp ../../../include/module/* ./
cp ../../../src/*.cpp ./
cp ../../../src/module/*.cpp ./


if [ "$(uname)" == 'Darwin' ]; then

  cp ../../../src/HIDAPI/mac/hid.c ./
  swig -c++ -ruby tbi.i
  ruby extconf.rb

elif [ "$(expr substr $(uname -s) 1 5)" == 'Linux' ]; then

  cp ../../../src/HIDAPI/libusb/hid.c ./
  swig -c++ -ruby tbi.i
  ruby extconf.rb --with-opt-include=/usr/include/libusb-1.0

elif [ "$(expr substr $(uname -s) 1 10)" == 'MINGW32_NT' ]; then                                                                                           

  cp ../../../src/HIDAPI/windows/hid.c ./
  swig -c++ -ruby tbi.i
  ruby extconf.rb

else

  echo "Your platform ($(uname -a)) is not supported."
  exit 1

fi

make
cp ./tbi.so ../samples
