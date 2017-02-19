#!/usr/bin/env ruby

$:.unshift File.join(File.dirname(__FILE__), ".")
require 'tbi'


chopper = Tbi::Chopper.new

chopper.disableAllUsbPort()
chopper.enableAllUsbPort()

chopper.disableUsbPort(1)
chopper.disableUsbPort(2)


