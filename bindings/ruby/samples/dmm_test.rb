#!/usr/bin/env ruby

$:.unshift File.join(File.dirname(__FILE__), ".")
require 'tbi'

dmm = Tbi::Dmm.new
dmm.open()

puts sprintf("%.3f [V]", dmm.getVoltage())
puts sprintf("%.3f [mA]", 1000.0 * dmm.getCurrent())
