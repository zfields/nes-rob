/*
  Blink R.O.B.'s LED

  The light emitting diode (LED) on R.O.B.'s head will turn on for one second,
  then off again for one second, indefinitely. This sketch works by blinking
  commands over an LED connected to `LED_BUILTIN`. When those flashes are viewed
  by R.O.B., he will respond to the commands by blinking his own LED. This
  sketch is designed to elicit a simple response from R.O.B. and validate your
  hardware configuration.

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

void loop() {
  rob.sendCommand(NesRob::Command::LED_ENABLE);
  ::delay(1000);  // wait for a second
  rob.sendCommand(NesRob::Command::LED_DISABLE);
  ::delay(1000);  // wait for a second
}
