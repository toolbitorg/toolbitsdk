import tbi
import time

tbit = tbi.Tbit()

print tbit.gpio.read()
print tbit.gpio.digitalWrite(15, True)
time.sleep(0.5)
print tbit.gpio.digitalWrite(15, False)

led = tbit.newPinObj(15)
led = tbi.Pin(tbit.gpio, 15)

time.sleep(0.5)
led.on()
time.sleep(0.5)
led.off()



