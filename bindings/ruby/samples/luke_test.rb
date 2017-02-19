#!/usr/bin/env ruby

$:.unshift File.join(File.dirname(__FILE__), ".")
require 'tbi'

luke = Tbi::Luke.new

puts sprintf("%.3f [V]", luke.getVoltage())
puts sprintf("%.3f [mA]", 1000.0 * luke.getCurrent())

