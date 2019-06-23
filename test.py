#!/usr/bin/env python

import serial
import time

arduino = serial.Serial(
	port="/dev/cu.wchusbserialfa210",
	baudrate=9600,
	timeout=3,
	bytesize=serial.EIGHTBITS
)
time.sleep(3)
arduino.write('... --- ...\n')
time.sleep(1)
out=''
while arduino.inWaiting() > 0:
    out += arduino.read(40)

if out != '':
    print(">>" + out)

arduino.close()
