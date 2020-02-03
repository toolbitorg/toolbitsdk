from toolbit import Chopper
import time

chopper = Chopper()
chopper.open()

chopper.enableAllUsbPort()
print(chopper.getUsbPortStatus())

time.sleep(0.5)
chopper.disableAllUsbPort()
print(chopper.getUsbPortStatus())

time.sleep(0.5)
chopper.enableUsbPort(1)
print(chopper.getUsbPortStatus())

time.sleep(0.5)
chopper.enableUsbPort(2)
print(chopper.getUsbPortStatus())

time.sleep(0.5)
chopper.disableUsbPort(1)
print(chopper.getUsbPortStatus())

time.sleep(0.5)
chopper.disableUsbPort(2)
print(chopper.getUsbPortStatus())
