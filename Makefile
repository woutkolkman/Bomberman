BOARD_TAG = uno
USER_LIB_PATH = libraries
ARDUINO_LIB_PATH = /home/$(USER)/sketchbook/libraries
ARDUINO_LIBS = Wire USART CSPI IR

//LOCAL_CPP_SRCS += $(wildcard libraries/IR/*.cpp)
LOCAL_CPP_SRCS += $(wildcard libraries/Nunchuk/*.cpp)
LOCAL_CPP_SRCS += $(wildcard *.cpp)

include /usr/share/arduino/Arduino.mk
