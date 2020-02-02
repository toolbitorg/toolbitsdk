from toolbit import TbiDeviceManager, Dmm

devm = TbiDeviceManager()
devm.showDeviceList()

dmm = Dmm()
dmm.open()
print("Manufacturer:" + dmm.getVendorName())
print("Product     :" + dmm.getProductName())
print("Serial      :" + dmm.getProductSerial())
