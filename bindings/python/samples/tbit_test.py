import tbi
import time

tbit = tbi.Tbit()

print tbit.gpio.read()
tbit.gpio.digitalWrite(15, True)
time.sleep(0.5)
tbit.gpio.digitalWrite(15, False)

led = tbi.Pin(tbit.gpio, 15)
outpin = tbi.Pin(tbit.gpio, 6, tbi.OUTPUT_PIN)
inpin = tbi.Pin(tbit.gpio, 5, tbi.INPUT_PULLUP_PIN)

time.sleep(0.5)
led.on()
outpin.on()
print inpin.value()

time.sleep(0.5)
led.off()
outpin.off()
print inpin.value()



