import tbi

chopper = tbi.Chopper()

chopper.disableAllUsbPort()
chopper.enableAllUsbPort()

chopper.disableUsbPort(1)
chopper.disableUsbPort(2)
