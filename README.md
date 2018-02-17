# AMO-Electronics
Collection of electronics projects intended for conducting atomic physics experiments.


## ECDL_CUR_CTRL
This folder contains the schematics and board layout for an ultra-low noise laser diode current controller. It builds upon proven designs of Libbrecht & Hall (https://doi.org/10.1063/1.1143949) as well as Erickson et. al. (https://doi.org/10.1063/1.2953597).

## Analog Temp Controller
This folder contains the schematics and board layout for a thermoelectric cooler controller. It features a PID-loop that drives a Peltier element (or alternatively a resistive heater) in order to match the resistance of a NTC thermistor to a given set temperature.

<<<<<<< HEAD
## Pfeiffer Compact Gauge Controller
A small standalone board which can be used to interface the Pfeiffer PKR/IKR series compact vacuum gauges. Features an ATMEGA32U4 microcontroller to convert the measurement signal to a pressure and provide it via the built-in USB interface or a I2C/SPI display. The accompanying firmware (in form of an Arduino sketch) can be found in the FW folder.
=======
## Pfeiffer_Compact_Gauge_Controller
This folder contains the schematics and board layout for a circuit that can be used to interface the Pfeiffer PKR/IKR Series Compact Vacuum Gauges. A microcontroller detects which gauge has been connected and reads the current pressure. The pressure values can be directly displayed via a SPI/I2C Display or sent to further equipment via the USB port.
>>>>>>> origin/master
