#!/bin/sh

g++ -fprofile-arcs -ftest-coverage -Wall -Wpedantic -O0 -g \
  NesRob.test.cpp \
  signal_generator.test.cpp \
  ../src/signal_generator.cpp \
  ../src/signal_generator_error.cpp \
  led_ntsc_driver.test.cpp \
  ../src/led_ntsc_driver.cpp \
  w_wave_driver.test.cpp \
  ../src/w_wave_driver.cpp \
  ../src/pulse_driver_error.cpp \
  ../src/hal_error.cpp \
-I. \
-I ../src/ \
-I Catch2/single_include/ \
-I FakeIt/single_header/catch/ \
-DRUN_ALL_TESTS \
-o nes_rob_tests \
&& ./nes_rob_tests \
&& gcovr --print-summary --sort-percentage --exclude-throw-branches --delete \
  --object-directory . \
  --root ../src \
  --exclude .*_error.* \
&& rm *.gcno
