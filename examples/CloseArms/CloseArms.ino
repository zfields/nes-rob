/*
  Close R.O.B.'s Arms

  Turns on and off a light emitting diode (LED) connected to a digital pin to
  send control signals to the NES R.O.B. When R.O.B. is powered on, it executes
  a calibration routine, which leaves it facing forward with arms open. This
  sketch causes R.O.B.'s arms to close, validating your hardware configuration.

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

// Blink command at 1 Hz
void loop() {
  rob.sendCommand(NesRob::Command::ARMS_CLOSE);
  ::delay(1000);
}
