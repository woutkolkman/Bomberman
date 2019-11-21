all:
	gcc -o main main.cpp /media/sf_Bomberman/libraries/IR/ir.cpp

BOARD_TAG = uno
ARDUINO_LIBS = Wire USART CSPI
include /usr/share/arduino/Arduino.mk