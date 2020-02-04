from toolbit import TbiDeviceManager, Dmm

devm = TbiDeviceManager()
dev_num = devm.getDeviceNum("DMM")
serial_list = devm.getSerialList("DMM")
print("Toolbit DMM")
print("  Num    :", dev_num)
print("  Serial :", serial_list)
print("")

dmm = Dmm()
for serial in serial_list:
    dmm.open(serial)
    print("Manufacturer : " + dmm.getVendorName())
    print("Product      : " + dmm.getProductName())
    print("Serial       : " + dmm.getProductSerial())
    print("")
    dmm.close()
