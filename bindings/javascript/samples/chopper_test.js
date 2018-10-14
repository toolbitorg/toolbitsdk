const Chopper=require('./tbi.node').Chopper;

chopper = new Chopper();

chopper.enableAllUsbPort()
chopper.getUsbPortStatus()

//sleep(0.5)
chopper.disableAllUsbPort()
chopper.getUsbPortStatus()

//sleep(0.5)
chopper.enableUsbPort(1)
chopper.getUsbPortStatus()

//sleep(0.5)
chopper.enableUsbPort(2)
chopper.getUsbPortStatus()

//sleep(0.5)
chopper.disableUsbPort(1)
chopper.getUsbPortStatus()

//sleep(0.5)
chopper.disableUsbPort(2)
chopper.getUsbPortStatus()
