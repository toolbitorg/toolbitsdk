ifeq ($(OS), Windows_NT)
	TARGET = toolbit/_toolbit*.dll
	PYTHON = python
else
	UNAME := $(shell uname)
	ifeq ($(UNAME), Linux)
		TARGET = toolbit/_toolbit.so
		PYTHON = python3
	endif
	ifeq ($(UNAME), Darwin)
		TARGET = toolbit/_toolbit*.so
		PYTHON = python3
	endif
endif


# implementation

all: $(TARGET)

FORCE:

$(TARGET):
	@[ -d toolbit ] || mkdir -p toolbit
	cp -f ../../../include/*.h toolbit
	cp -f ../../../include/module/*.h toolbit
	cp -f ../../../src/module/*.cpp toolbit
	cp -f ../../../src/*.cpp toolbit
	@[ -d toolbit/macos ] || mkdir -p toolbit/macos
	@[ -d toolbit/linux ] || mkdir -p toolbit/linux
	@[ -d toolbit/mswin ] || mkdir -p toolbit/mswin
	cp -f ../../../src/hidapi/linux/hid.c toolbit/linux
	cp -f ../../../src/hidapi/mac/hid.c toolbit/macos
	cp -f ../../../src/hidapi/windows/hid.c toolbit/mswin
	cp -f ../../toolbit.i toolbit
	cd toolbit; swig -c++ -python toolbit.i
	mv -f toolbit/toolbit.py toolbit/__init__.py
	$(PYTHON) setup.py build_ext --inplace

install: $(TARGET)
	$(PYTHON) setup.py install

clean:
	rm -fr build
	rm -fr toolbit

.PHONY: all clean
