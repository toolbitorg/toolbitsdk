import tbi
import time

tbit = tbi.Tbit()

print tbit.gpio.read()
print tbit.gpio.digitalWrite(15, True)
time.sleep(0.5)
print tbit.gpio.digitalWrite(15, False)

