# AVR-PowerMeter

## Introduction
This is the collaborative graduation project of ITI Basic Embedded System Track. It was prepared by:
1. Ahmed Aly
2. Marawan Ahmed
3. Mostafa Sayed
4. Mohamed Osama

## About The Project
This is a DC powermeter that utilizes both an ACS712 current sensor and a voltage-divider-based voltage sensor. These sensors' readings provide the ability to calculate both power and energy through software. The system is able to display readings on an LCD---as floats---and choose what to display: current, voltage, power, or energy. There is also a reset switch that nullifies all readings.

## Project Description
The system is mostly interrupt-driven: the sensors' readings are taken every second and both power and energy updated---Overflow mode in timer0 is used; the mode switch is connected to external interrupt 0 and reset switch is connected to external interrupt 1. The reading displayed on the LCD is only updated once every second. Due to the lack of time, the system was implemented using superloop architecture. Further plans to improve this system include:
1. Add the ability to read/calculate AC values (inst/rms).
2. Use a realtime operating system.
3. Interface with the LCD using I2C.

