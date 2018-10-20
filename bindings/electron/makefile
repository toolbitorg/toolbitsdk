ifeq ($(OS), Windows_NT)
	include makefile.mingw
else
	UNAME := $(shell uname)
	ifeq ($(UNAME), Linux)
		include makefile.gcc
	endif
	ifeq ($(UNAME), Darwin)
		include makefile.macos
	endif
endif

