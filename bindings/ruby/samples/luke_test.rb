#!/usr/bin/env ruby

$:.unshift File.join(File.dirname(__FILE__), ".")
require 'tbi'


luke = Tbi::Luke.new

p luke.getVoltage()
p luke.getCurrent()

