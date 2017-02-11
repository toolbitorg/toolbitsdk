rm -fr *.h *.cpp *.so *.o *.cxx
cp ../../../include/* ./
cp ../../../src/*.cpp ./
cp ../../../src/HIDAPI/libusb/hid.c ./
swig -c++ -ruby libtbi.i
ruby extconf.rb --with-opt-include=/usr/include/libusb-1.0
make
cp ./libtbi.so ../sample
