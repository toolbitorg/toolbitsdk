rm -fr *.h *.cpp *.so *.o *.cxx *.c
cp ../../../include/* ./
cp ../../../src/*.cpp ./
cp ../../../src/HIDAPI/libusb/hid.c ./
swig -c++ -python libtbi.i
python setup.py build_ext --inplace
cp libtbi.py _libtbi.so ../samples/
