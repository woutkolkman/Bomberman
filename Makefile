BOARD_TAG = uno
USER_LIB_PATH = libraries
ARDUINO_LIB_PATH = /usr/share/arduino/libraries
ARDUINO_LIBS = Wire USART SPI IR Nunchuk Adafruit_GFX_Library Adafruit_ILI9341

//LOCAL_CPP_SRCS += $(wildcard libraries/IR/*.cpp)
LOCAL_CPP_SRCS += $(wildcard libraries/Nunchuk/*.cpp)
LOCAL_CPP_SRCS += $(wildcard *.cpp)

include /usr/share/arduino/Arduino.mk
