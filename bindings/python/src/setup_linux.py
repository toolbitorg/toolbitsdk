from distutils.core import setup, Extension

tbi_module = Extension('_tbi',
                    sources = ['tbi_wrap.cxx', 'tbi_core.cpp', 'tbi_device.cpp', 'tbi_device_manager.cpp', 'tbi_service.cpp', 'attribute.cpp', 'tbit.cpp', 'hid.c', 'basicdemo.cpp', 'chopper.cpp', 'luke.cpp', 'adc.cpp', 'adc_hw.cpp', 'gpio_hw.cpp', 'i2c_hw.cpp', 'pin.cpp'],
                    include_dirs=['/usr/include/libusb-1.0'],
                    libraries=['usb-1.0', 'udev'],
                    extra_compile_args=["-std=gnu++11"],
                )

setup (name = 'tbi',
       version = '1.0',
       description = 'This is a libtbi package',
       ext_modules = [tbi_module],
       py_modules = ["tbi"],)
