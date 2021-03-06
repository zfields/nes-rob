/*
  Twist R.O.B.'s Torso Left and Right

  The Nintendo R.O.B. comprises of three electric motors, which enable movement.

  1. Base - Turns torso right or left.
  2. Right Shoulder - Move shoulders up or down.
  3. Left Shoulder - Adjust arms open or close.

  This sketch is designed to exercise the base motor, which will cause
  R.O.B.'s torso to twist left and right.

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
  // put your setup code here, to run once:

}

// Exercise Base Motor
void loop() {
  rob.sendCommand(NesRob::Command::LEFT);
  ::delay(3000);  // wait for 3 seconds
  rob.sendCommand(NesRob::Command::RIGHT);
  ::delay(3000);  // wait for 3 seconds
}
