#!/usr/bin/env ruby

$:.unshift File.join(File.dirname(__FILE__), ".")
require 'libtbi'


luke = Libtbi::Luke.new

p luke.getVoltage()
p luke.getCurrent()

