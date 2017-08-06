#!/bin/bash

rm -fr *.h *.cpp *.so *.o *.cxx *.c tbi.py _tbi.so
cp ../../../include/* ./
cp ../../../include/module/* ./
cp ../../../src/*.cpp ./
cp ../../../src/module/*.cpp ./


if [ "$(uname)" == 'Darwin' ]; then

  cp ../../../src/HIDAPI/mac/hid.c ./
  swig -c++ -python tbi.i
  python setup.py build_ext --inplace

elif [ "$(expr substr $(uname -s) 1 5)" == 'Linux' ]; then

  cp ../../../src/HIDAPI/libusb/hid.c ./
  swig -c++ -python tbi.i
  python setup_linux.py build_ext --inplace

#elif [ "$(expr substr $(uname -s) 1 10)" == 'MINGW32_NT' ]; then                                                                                           
#

else

  echo "Your platform ($(uname -a)) is not supported."
  exit 1

fi

cp tbi.py _tbi.so  ../samples/
