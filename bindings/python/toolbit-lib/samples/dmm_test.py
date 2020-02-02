from toolbit import Dmm

dmm = Dmm()
dmm.open()
print(str('%03.3f' % round(dmm.getVoltage(),3)) + " [V]")
print(str('%03.3f' % (1000.0 * dmm.getCurrent())) + " [mA]")
