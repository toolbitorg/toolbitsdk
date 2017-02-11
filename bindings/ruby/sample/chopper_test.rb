#!/usr/bin/env ruby

$:.unshift File.join(File.dirname(__FILE__), ".")
require 'libtbi'


chopper = Libtbi::Chopper.new

chopper.disableAllUsbPort()
chopper.enableAllUsbPort()

chopper.disableUsbPort(1)
chopper.disableUsbPort(2)


