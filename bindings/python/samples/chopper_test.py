import libtbi

chopper = libtbi.Chopper()

chopper.disableAllUsbPort()
chopper.enableAllUsbPort()

chopper.disableUsbPort(1)
chopper.disableUsbPort(2)
