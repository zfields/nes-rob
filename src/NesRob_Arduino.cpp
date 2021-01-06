#include "NesRob.h"

#include <Arduino.h>

NesRob::NesRob (
  unsigned int led_pin_
) :
  _led_pin(led_pin_)
{
  ::pinMode(_led_pin, OUTPUT);
  ::digitalWrite(_led_pin, LOW);
}

void
NesRob::blinkCommand (
  Command command_
) {
  // Send initialization sequence
  ::delayMicroseconds(66666); // 0000 (required delay between commands)
  {
    ::digitalWrite(_led_pin, HIGH);
    ::delayMicroseconds(1500);
    ::digitalWrite(_led_pin, LOW);
    ::delayMicroseconds(15166);
  } // 1
  ::delayMicroseconds(16666); // 0

  // Flash command sequence
  for (int i = 7 ; i >= 0 ; --i) {
    unsigned int state = ((static_cast<unsigned int>(command_) >> i) & static_cast<unsigned int>(0x1));
    ::digitalWrite(_led_pin, (state ? HIGH : LOW));
    ::delayMicroseconds(1500);
    ::digitalWrite(_led_pin, LOW);
    ::delayMicroseconds(15166);
  }
}
