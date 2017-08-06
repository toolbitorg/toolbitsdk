#!/usr/bin/env ruby

$:.unshift File.join(File.dirname(__FILE__), ".")
require 'tbi'

tbit = Tbi::Tbit.new

tbit.gpio.digitalWrite(15, 1);
puts sprintf("%.32b ", tbit.gpio.read())
sleep(0.5)
tbit.gpio.digitalWrite(15, 0);
puts sprintf("%.32b ", tbit.gpio.read())

puts sprintf("%.32b ", tbit.adc.analogRead(0))

