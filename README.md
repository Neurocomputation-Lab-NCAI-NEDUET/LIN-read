# LIN-read
This code reads LIN data from wire between motor controller (VOTOL EM-100) and speedometer.
It runs on an Arduino UNO where pin 12 is tapped and pulses are read.
Reads duration of HIGH pulses
The code prints Speed (calibrated), Gear, brake status, throttle status from LIN data.