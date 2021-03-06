/*
  Prepare R.O.B. for storage in his original packaging

  First, the recalibration routine executes, leaving R.O.B. in a known state.
  Then the subsequent commands return R.O.B. to the position required to fit in
  the styrofoam mold of the original packaging.

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

// Put R.O.B. into known position, then prepare for storage
void setup() {
  rob.sendCommand(NesRob::Command::RECALIBRATE);
  ::delay(11500);  // wait for 11.5 seconds
  rob.sendCommand(NesRob::Command::DOWN_2);
  ::delay(3500);  // wait for 3.5 seconds
  rob.sendCommand(NesRob::Command::DOWN_2);
  ::delay(3500);  // wait for 3.5 seconds
  rob.sendCommand(NesRob::Command::DOWN);
  ::delay(2500);  // wait for 2.5 seconds
  rob.sendCommand(NesRob::Command::CLOSE);
}

void loop() {
  // put your main code here, to run repeatedly:

}
