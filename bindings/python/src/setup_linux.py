from distutils.core import setup, Extension

tbi_module = Extension('_tbi',
                    sources = ['tbi_wrap.cxx', 'tbi_core.cpp', 'tbi_device.cpp', 'tbi_service.cpp', 'attribute.cpp', 'pic16f145x.cpp', 'hid.c', 'basicdemo.cpp', 'chopper.cpp', 'luke.cpp'],
                    include_dirs=['/usr/include/libusb-1.0'],
                    libraries=['usb-1.0', 'udev'],
                )

setup (name = 'tbi',
       version = '1.0',
       description = 'This is a libtbi package',
       ext_modules = [tbi_module],
       py_modules = ["tbi"],)
