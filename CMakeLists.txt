##
#The MIT License (MIT)
#
# Copyright (c) 2013 Jerome Quere <contact@jeromequere.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
##

cmake_minimum_required(VERSION 2.6)
project(ARDUINIO)


#Card specific configuration
set(MMCU "atmega328p")
set(SEND_SPEED "57600")
set(SEND_TTY "/dev/ttyUSB0")

#Compiler options
set(CMAKE_CXX_COMPILER "avr-g++")
set(CMAKE_CXX_FLAGS  "-mmcu=${MMCU} -Os -Wall -fno-exceptions -ffunction-sections -fdata-sections -DF_CPU=16000000L -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=105 -Wl,--gc-sections")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

#Arduino folder
set(AR_DIR "/usr/share/arduino")
set(AR_INCLUDE_DIR "${AR_DIR}/hardware/arduino/cores/arduino/" "${AR_DIR}/hardware/arduino/variants/standard")

#Library ressources
set(NAME "arduinio")
set(SRC_DIR "src")
set(INCLUDES_DIR "includes")

list(APPEND SRCS "${SRC_DIR}/IOService.cpp")
list(APPEND SRCS "${SRC_DIR}/IOStream.cpp")
list(APPEND SRCS "${SRC_DIR}/TimePoint.cpp")


#Create library
add_library(${NAME} STATIC ${SRCS})
include_directories(${INCLUDES_DIR} ${AR_INCLUDE_DIR})

#Prepare tests
set(EXEMPLE_DIR "exemples")
find_library(AR_LIB "arduino_${MMCU}" PATH ${LIB_DIR})


#Exemple 1: Blink
set(EXEMPLE1_NAME blink)
set(EXEMPLE1_HEXNAME "${EXEMPLE1_NAME}.hex")
list(APPEND EXEMPLE1_SRCS "${EXEMPLE_DIR}/blink.cpp")
add_executable(${EXEMPLE1_NAME} ${EXEMPLE1_SRCS})
target_link_libraries(${EXEMPLE1_NAME} ${NAME} ${AR_LIB})
add_custom_command(TARGET ${EXEMPLE1_NAME} POST_BUILD COMMAND avr-objcopy -R .eeprom -O ihex ${EXEMPLE1_NAME} ${EXEMPLE1_HEXNAME})
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ${EXEMPLE1_HEXNAME})


#Send custom target: make send will send test 1 to the arduino.
add_custom_target(send avrdude -p ${MMCU} -c STK500v1 -b ${SEND_SPEED} -P ${SEND_TTY} -carduino -U "flash:w:${EXEMPLE1_HEXNAME}")