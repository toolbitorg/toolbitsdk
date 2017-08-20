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

led = Tbi::Pin.new(tbit.gpio, 15)
outpin = Tbi::Pin.new(tbit.gpio, 6, Tbi::OUTPUT_PIN)
inpin = Tbi::Pin.new(tbit.gpio, 5, Tbi::INPUT_PULLUP_PIN)

sleep(0.5)
led.on()
outpin.on()
puts inpin.value()

sleep(0.5)
led.off()
outpin.off()
puts inpin.value()

