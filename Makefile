BOARD_TAG = uno
USER_LIB_PATH = libraries
ARDUINO_LIB_PATH = /usr/share/arduino/libraries
ARDUINO_LIBS = Wire USART CSPI IR

//LOCAL_CPP_SRCS += $(wildcard libraries/IR/*.cpp)
//LOCAL_CPP_SRCS += $(wildcard *.cpp)

include /usr/share/arduino/Arduino.mk
