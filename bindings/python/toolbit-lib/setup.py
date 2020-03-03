#!/usr/bin/env python
"""
Toolbit SDK
Copyright (C) 2020 Junji Ohama <junji.ohama@toolbit.org>

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
more details.
"""

try:
    from setuptools import setup, Extension
except ImportError:
    from distutils.core import setup, Extension
import platform
from os import path
from io import open

# Get the long description from the README file
here = path.abspath(path.dirname(__file__))
with open(path.join(here, 'README.md'), encoding='utf-8') as f:
    long_description = f.read()

sources = ['toolbit/toolbit_wrap.cxx','toolbit/tbi_core.cpp',
    'toolbit/tbi_device.cpp', 'toolbit/tbi_service.cpp', 'toolbit/attribute.cpp',
    'toolbit/tbit.cpp', 'toolbit/chopper.cpp',
    'toolbit/dmm.cpp', 'toolbit/tbi_device_manager.cpp', 'toolbit/adc.cpp',
    'toolbit/adc_hw.cpp', 'toolbit/gpio_hw.cpp', 'toolbit/i2c_hw.cpp',
    'toolbit/pin.cpp']

headers = ['toolbit/hidapi.h', 'toolbit/tbi_core.h',
    'toolbit/tbi_device.h', 'toolbit/tbi_service.h', 'toolbit/attribute.h',
    'toolbit/tbit.h', 'toolbit/chopper.h',
    'toolbit/dmm.h', 'toolbit/tbi_device_manager.h', 'toolbit/adc.h',
    'toolbit/adc_hw.h', 'toolbit/gpio_hw.h', 'toolbit/i2c_hw.h',
    'toolbit/pin.h']


osname = platform.system()
if osname == 'Linux':
    toolbit_module = [
        Extension('toolbit._toolbit',
            sources + ['toolbit/linux/hid.c'],
            include_dirs=['toolbit'],
            libraries=['udev'],
            extra_compile_args=["-std=gnu++11"],
    )]
elif osname == 'Darwin':
    import sys, os
    from distutils.util import get_platform
    temp_dir = "temp.%s-%d.%d" % (get_platform(), *sys.version_info[:2])
    os.environ['LDFLAGS'] = '-framework IOKit -framework Carbon'
    # Cannot mix .c and .cpp files in one module
    # Because clang doesn't allow to compile .c file with -std=c++11 option
    # Threfore, compile hid.c first and then build toolbit extension with hid.o
    toolbit_module = [
        Extension('toolbit._hidapi',
            ['toolbit/macos/hid.c'],
            include_dirs=['toolbit']
        ),
        Extension('toolbit._toolbit',
            sources,
            include_dirs=['toolbit'],
            extra_compile_args=['-std=c++11'],
            extra_objects=['build/' + temp_dir + '/toolbit/macos/hid.o'],
            libraries=['stdc++'],
        )
    ]
elif osname == 'Windows':
    toolbit_module = [
        Extension('toolbit._toolbit',
            sources + ['toolbit/mswin/hid.c'],
            include_dirs=['toolbit'],
            libraries=['setupapi'],
    )]

setup (
    name = 'toolbit-lib',
    version = '1.0.0',
    description = 'Toolbit library',
    long_description = long_description,
    long_description_content_type='text/markdown',
    url = 'https://github.com/toolbitorg/ToolbitSDK',
    author ='Junji Ohama',
    author_email = 'junji.ohama@toolbit.org',
    classifiers=[  # Optional
        # How mature is this project? Common values are
        #   3 - Alpha
        #   4 - Beta
        #   5 - Production/Stable
        'Development Status :: 4 - Beta',

        # Indicate who your project is intended for
        'Intended Audience :: Developers',
        'Topic :: Software Development :: Libraries :: Python Modules',

        # Pick your license as you wish
        'License :: OSI Approved :: GNU General Public License v2 (GPLv2)',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.6',
        'Programming Language :: Python :: 3.7',
        'Programming Language :: Python :: 3.8',
    ],
    keywords = 'toolbit sdk library',
    packages=['toolbit'],
    python_requires='>=3.6',
    #install_requires = [''],
    #entry_points={  # Optional
    #    'console_scripts': [
    #        'sample=sample:main',
    #    ],
    #},
    ext_modules = toolbit_module,
    data_files = [
        ('header', headers),
        ('source', ['toolbit/linux/hid.c', 'toolbit/macos/hid.c', 'toolbit/mswin/hid.c'])
    ],
    project_urls={
        'Bug Reports': 'https://github.com/toolbitorg/ToolbitSDK/issues',
        'Source': 'https://github.com/toolbitorg/ToolbitSDK',
    },
)
