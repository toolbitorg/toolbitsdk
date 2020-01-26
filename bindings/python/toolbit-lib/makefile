ifeq ($(OS), Windows_NT)
	TARGET = toolbit/_toolbit*.dll
else
	UNAME := $(shell uname)
	ifeq ($(UNAME), Linux)
		TARGET = toolbit/_toolbit.so
	endif
	ifeq ($(UNAME), Darwin)
		TARGET = toolbit/_toolbit.so
	endif
endif


# implementation

all: $(TARGET)

FORCE:

$(TARGET):
	cp -f ../../../include/*.h toolbit
	cp -f ../../../include/module/*.h toolbit
	cp -f ../../../src/module/*.cpp toolbit
	cp -f ../../../src/*.cpp toolbit
	@[ -d toolbit/macos ] || mkdir -p toolbit/macos
	@[ -d toolbit/linux ] || mkdir -p toolbit/linux
	@[ -d toolbit/mswin ] || mkdir -p toolbit/mswin
	cp -f ../../../src/HIDAPI/linux/hid.c toolbit/linux
	cp -f ../../../src/HIDAPI/mac/hid.c toolbit/macos
	cp -f ../../../src/HIDAPI/windows/hid.c toolbit/mswin
	cp -f ../../toolbit.i toolbit
	cd toolbit; swig -c++ -python toolbit.i
	mv -f toolbit/toolbit.py toolbit/__init__.py
	python setup.py build_ext --inplace

install: $(TARGET)
	python setup.py install

clean:
	rm -fr build
	rm -fr toolbit/*.h
	rm -fr toolbit/*.cpp
	rm -fr toolbit/*.cxx
	rm -fr toolbit/*.c
	rm -fr toolbit/*.i
	rm -fr toolbit/_*.*

.PHONY: all clean
