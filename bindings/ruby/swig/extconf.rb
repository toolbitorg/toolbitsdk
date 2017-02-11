require 'mkmf'

$libs += " -lstdc++ -lusb-1.0 -lpthread"
create_makefile("libtbi")
