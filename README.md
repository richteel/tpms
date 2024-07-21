# Raspberry Pi Pico Tire/Tyre Pressure Monitoring System (TPMS) Monitor

The Tire light was illuminated on the dash of my 2007 Prius. I ran around checking the air pressure in the tires. Found that a few were perhaps a little low, but not enough to cause the dash light to be lit. I then assumed that one or more of the TPMS sensors had a dead battery, but how can I know for certain? I took it to the garage and found that yes, one was dead and one had a low battery. The garage replaced them both. This got me to look and see if anyone had built a TPMS display to show the pressure and temperature of each tire.

After searching a bit, I came across an article on <a href="https://www.hackster.io/jsmsolns/arduino-tpms-tyre-pressure-display-b6e544" target="_blank">hackster.io</a> titled, "Arduino TPMS Tyre Pressure Display". It was just the thing I was looking for. I wanted to use a Raspberry Pi Pico as I have a few of them here, but the code posted does not support the RP2040 micro-controller used in the Raspberry Pi Pico. I was able to modify the code to work with the RP2040. My code will be available on GitHub at <a href="https://github.com/richteel/tpms" target="_blank">https://github.com/richteel/tpms</a> and some posts available at <a href="https://teelsys.com/" target="_blank">https://teelsys.com/</a>.

Newer cars have the details of the TPMS built in so it is not necessary to guess, but my older Prius does not. With this project, I will be able to monitor the health of my tires and when on a road trip and the dash light comes on, I don't need to panic and pull over to see if it is a major issue, that needs to be resolved right away, or if it is something that I can wait until I get to my destination.


## Items used in my build ##

- <a href="https://www.adafruit.com/product/4883" target="_blank">Raspberry Pi Pico (Pimoroni Pico Lipo) NOTE: Used Earle Philhower's core</a>
- <a href="https://www.adafruit.com/product/358" target="_blank">Adafruit 1.8" Color TFT LCD display with MicroSD Card Breakout - ST7735R</a>
- <a href="https://www.amazon.com/gp/product/B0C8RRG88V/ref=ppx_yo_dt_b_asin_title_o04_s00?ie=UTF8&psc=1" target="_blank">CC1101 Radio Frequency Transceiver Module</a>
- <a href="https://www.adafruit.com/product/160" target="_blank">Buzzer</a>
- 1 10 Ohm Resistor
- 2 150 Ohm Resistors
- <a href="https://www.pcbway.com/project/shareproject/Raspberry_Pi_Pico_Tire_Tyre_Pressure_Monitoring_System_TPMS_48b6424e.html" target="_blank">PCB from PCBWay</a>

## Code Notes ##

### TPMS_Monitor ###
The code in the TPMS_Monitor folder is the original code modified to work with the Raspberry Pi Pico code using Earle Philhower's core. This code is hard coded for US 315 MHz and Toyota PMV-107J sensors.

### TPMS_Monitor2 ###
Currently a work in progress to allow configuration to any supported sensor configuration. This code is not ready for use. Code changes will be checked in occasionally as code is updated. An Excel workbook, TPMS_Monitor2.xlsx, has been added with some analysis to help with the development of the modified version.

---

I hope you enjoy this project and have success building it.

<a href="https://www.pcbway.com/project/shareproject/Raspberry_Pi_Pico_Tire_Tyre_Pressure_Monitoring_System_TPMS_48b6424e.html"><img src="https://www.pcbway.com/project/img/images/frompcbway-1220.png" alt="PCB from PCBWay" /></a>
