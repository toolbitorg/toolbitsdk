#!/usr/bin/env ruby

$:.unshift File.join(File.dirname(__FILE__), ".")
require 'tbi'

tbit = Tbi::Tbit.new

tbit.gpiohw.digitalWrite(15, 1);
puts sprintf("%.32b ", tbit.gpiohw.read())
sleep(0.5)
tbit.gpiohw.digitalWrite(15, 0);
puts sprintf("%.32b ", tbit.gpiohw.read())

puts sprintf("%.32b ", tbit.adchw.analogRead(0))

led = Tbi::Pin.new(tbit, 15, Tbi::OUTPUT_PIN)
outpin = Tbi::Pin.new(tbit, 6, Tbi::OUTPUT_PIN)
inpin = Tbi::Pin.new(tbit, 5, Tbi::INPUT_PULLUP_PIN)
adcpin = Tbi::Adc.new(tbit, 4)

sleep(0.5)
led.on()
outpin.on()
puts inpin.value()
puts adcpin.value()

sleep(0.5)
led.off()
outpin.off()
puts inpin.value()
puts adcpin.value()

