require 'mkmf'

if RUBY_PLATFORM.downcase =~ /mswin(?!ce)|mingw|cygwin|bccwin/
  puts "Windows"
  $libs += " -lstdc++ -lsetupapi"
else
  puts "Linux"
  $libs += " -lstdc++ -lusb-1.0 -lpthread"
end

create_makefile("tbi")
