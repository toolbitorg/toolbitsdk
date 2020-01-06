from distutils.core import setup, Extension

tbi_module = Extension('_tbi',
                    sources = ['tbi_wrap.cxx', 'tbi_core.cpp', 'tbi_device.cpp',
                        'tbi_device_manager.cpp', 'tbi_service.cpp', 'attribute.cpp',
                        'tbit.cpp',
                        # Cannot mix .c and .cpp files because of -std=c++11 option
                        # 'hid.c',
                        'basicdemo.cpp', 'chopper.cpp',
                        'dmm.cpp', 'adc.cpp', 'adc_hw.cpp', 'gpio_hw.cpp',
                        'i2c_hw.cpp', 'pin.cpp'],
                    include_dirs=[],
#                    libraries=['stdc++ -framework IOKit -framework Carbon'],
                    extra_compile_args=['-std=c++11'],
                )

setup (name = 'tbi',
       version = '1.0',
       description = 'This is a libtbi package',
       ext_modules = [tbi_module],
       py_modules = ["tbi"],)
