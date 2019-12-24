# Project JulIoT

## How to compile and flash board
Execute this command in the project directory:
```
make -f makeEspArduino.mk UPLOAD_PORT=/dev/tty.usbserial-14330 flash
```
* Note that all included libraries must be placed in the project directory.
* You may also need to specify the port of the device. Do that by setting the `UPLOAD_PORT` variable when running make.
* You can run `make  -f makeEspArduino.mk help` to print the available commands in the make script.

