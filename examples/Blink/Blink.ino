/*
  Blink R.O.B.'s LED

  Turns on and off a light emitting diode (LED) connected to LED_BUILTIN, which
  sends control signals to the NES R.O.B. When the LED signal is viewed by
  R.O.B., the LED on R.O.B.'s head will turn on for one second, then off for one
  second, repeatedly. R.O.B.'s response validates your hardware configuration.

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
  rob.sendCommand(NesRob::Command::LED_ENABLE);
  ::delay(1000);  // wait for a second
  rob.sendCommand(NesRob::Command::LED_DISABLE);
  ::delay(1000);  // wait for a second
}
