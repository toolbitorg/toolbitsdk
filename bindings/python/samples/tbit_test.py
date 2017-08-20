import tbi
import time

tbit = tbi.Tbit()

print tbit.gpiohw.read()
tbit.gpiohw.digitalWrite(15, True)
time.sleep(0.5)
tbit.gpiohw.digitalWrite(15, False)

led = tbi.Pin(tbit, 15, tbi.OUTPUT_PIN)
outpin = tbi.Pin(tbit, 6, tbi.OUTPUT_PIN)
inpin = tbi.Pin(tbit, 5, tbi.INPUT_PULLUP_PIN)
adcpin = tbi.Adc(tbit, 4)

time.sleep(0.5)
led.on()
outpin.on()
print inpin.value()
print adcpin.value()

time.sleep(0.5)
led.off()
outpin.off()
print inpin.value()
print adcpin.value()

