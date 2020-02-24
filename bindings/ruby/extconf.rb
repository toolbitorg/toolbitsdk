=begin
  Toolbit SDK
  Copyright (C) 2020 Junji Ohama <junji.ohama@toolbit.org>

  This program is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
  more details.
=end

require 'mkmf'

if RUBY_PLATFORM.downcase =~ /mswin(?!ce)|mingw|cygwin|bccwin/
  puts "Windows"
#  $libs += "-lsetupapi"
# The following options might be useful to distribute it for non MinGW users
  $libs += "-lsetupapi -static-libstdc++ -static-libgcc"

elsif RUBY_PLATFORM.downcase =~ /linux/
  puts "Linux"
  $CXXFLAGS = " -g -MMD -MP  -std=c++11 "
  $libs += " -lstdc++ -lusb-1.0 -ludev"

elsif RUBY_PLATFORM.downcase =~ /darwin/
  puts "macOS"
  $CXXFLAGS = " -g -MMD -MP  -std=c++11 "
  $libs += " -lstdc++ -framework IOKit -framework Carbon"

else
  puts "We're running under an unknown operating system."
end

create_makefile("tbi")
