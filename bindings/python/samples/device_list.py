from toolbit import TbiDeviceManager, TbiCore

devm = TbiDeviceManager()
tdev = TbiCore()

dev_list = devm.getDeviceList()
dev_list = tuple(set(dev_list))

print("The number of connected devices:", devm.getDeviceNum())

print("   {:14} {:16} {:10}".format("Manufacturer", "Product", "Serial"))
for dev in dev_list:
    serial_list = devm.getSerialList(dev)
    for serial in serial_list:
        tdev.openPath(devm.getPathByNameAndSerial(dev, serial))
        print("   {:14} {:16} {:10}".format(tdev.getVendorName(), tdev.getProductName(), tdev.getProductSerial()))
        tdev.close()
