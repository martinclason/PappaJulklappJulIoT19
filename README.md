# Project JulIoT

## How to compile and flash board
Execute this command in the project directory:
```
make -f makeEspArduino.mk UPLOAD_PORT=/dev/tty.usbserial-14330 SKETCH=sketch.ino flash
```
* Note that all included libraries must be placed in the project directory.
* You may also need to specify the port of the device. Do that by setting the `UPLOAD_PORT` variable when running make.
* You can run `make  -f makeEspArduino.mk help` to print the available commands in the make script.

## Generate QR-code
To generate QR-code and the text to init the bitmap data in the sketch run:
```
python generate_qr_text.py
```
* Note that ypur bitmap data needs to be in whole bytes for the display to display the bitmap properly. This is the reason that the data is padded with zeros.
* Note that you seem to need the PROGMEM modifier after the type declaration in the arduino sketch for the data to behave correctly.
