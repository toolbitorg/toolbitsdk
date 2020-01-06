import tbi

luke = tbi.Luke()
luke.open()

print(str('%03.3f' % round(luke.getVoltage(),3)) + " [V]")
print(str('%03.3f' % (1000.0 * luke.getCurrent())) + " [mA]")
