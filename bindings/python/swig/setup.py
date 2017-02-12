from distutils.core import setup, Extension

libtbi_module = Extension('_libtbi',
                    sources = ['libtbi_wrap.cxx', 'tbi_core.cpp', 'tbi_device.cpp', 'tbi_service.cpp', 'attribute.cpp', 'pic16f145x.cpp', 'hid.c', 'basicdemo.cpp', 'chopper.cpp', 'luke.cpp'],
                    include_dirs=['/usr/include/libusb-1.0'],
                    libraries=['usb-1.0', 'udev'],
                )

setup (name = 'libtbi',
       version = '1.0',
       description = 'This is a libtbi package',
       ext_modules = [libtbi_module],
       py_modules = ["libtbi"],)
