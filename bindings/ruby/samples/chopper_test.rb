#!/usr/bin/env ruby

$:.unshift File.join(File.dirname(__FILE__), ".")
require 'tbi'

chopper = Tbi::Chopper.new
chopper.open()

chopper.enableAllUsbPort()
p chopper.getUsbPortStatus()

sleep(0.5)
chopper.disableAllUsbPort()
p chopper.getUsbPortStatus()

sleep(0.5)
chopper.enableUsbPort(1)
p chopper.getUsbPortStatus()

sleep(0.5)
chopper.enableUsbPort(2)
p chopper.getUsbPortStatus()

sleep(0.5)
chopper.disableUsbPort(1)
p chopper.getUsbPortStatus()

sleep(0.5)
chopper.disableUsbPort(2)
p chopper.getUsbPortStatus()
