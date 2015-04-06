# rpi2edam
C++ program to interface the [InLog EDAM-5019](http://www.audon.co.uk/usb_multi/edam5019.html) thermocouple logger to the Raspberry Pi using RS-232.

## Software requirements
* [wiringPi](http://wiringpi.com)

## Hardware requirements
You will need to connect the EDAM-5019 to the Raspberry Pi's GPIO pins via an RS-232 transceiver. This is to convert the 3.3 V RPi signals to 12 V RS-232 signals required by the EDAM. The [TI MAX3232](http://www.ti.com/product/max3232) does the job nicely. You'll also need to enable the serial port. See info on the [eLinux wiki](http://elinux.org/RPi_Serial_Connection) for instructions.

Don't forget to set the correct address using the switches on the back of the EDAM. See the manual for instructions. The program expects it to be at address `01`.

## Build
Compile using `make` and then run `sudo ./rpi2edam`.

## Thermocouple types
Thermocouples are set to K-type. See the EDAM manual and the function `setType` if you need to change this.
