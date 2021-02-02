/*
  Prepare R.O.B. for storage in his original packaging

  Turns on and off a light emitting diode (LED) connected to LED_BUILTIN, which
  sends control signals to the NES R.O.B. When the LED signal is viewed by
  R.O.B., the calibration routine will execute and R.O.B. will return to the
  position required to fit inside the styrofoam mold of the original packaging.

  This sketch relies on timing delays to know when R.O.B. has finished executing
  each command, before submitting any subsequent commands. R.O.B.'s response
  validates your hardware configuration.

  The circuit:
  - Use the onboard LED (may require a brighter LED if the room is too bright).
  - Note: Most Arduinos have an on-board LED you can control. On the UNO, MEGA
    and ZERO it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN
    is set to the correct LED pin independent of which board is used.
    If you want to know what pin the on-board LED is connected to on your
    Arduino model, check the Technical Specs of your board at:
    https://www.arduino.cc/en/Main/Products

  created 2021
  by Zachary J. Fields

  This example code is in the public domain.
  http://www.github.com/zfields/nes-rob
*/

#include "NesRob.h"

NesRob rob(LED_BUILTIN);

void setup() {
  rob.sendCommand(NesRob::Command::CALIBRATE);
  ::delay(11500);  // wait for 11.5 seconds
  rob.sendCommand(NesRob::Command::ARMS_LOWER_2);
  ::delay(3500);  // wait for 3.5 seconds
  rob.sendCommand(NesRob::Command::ARMS_LOWER_2);
  ::delay(3500);  // wait for 3.5 seconds
  rob.sendCommand(NesRob::Command::ARMS_LOWER);
  ::delay(2500);  // wait for 2.5 seconds
  rob.sendCommand(NesRob::Command::ARMS_CLOSE);
}

void loop() {
  // put your main code here, to run repeatedly:

}
