NES R.O.B. Control Library
==========================

This library allows an Arduino board to control the Nintendo Entertainment
System Robot Operating Buddy (R.O.B.). This library has borrowed the research
done by x87bliss and those on the
[Atari Age Forums](https://atariage.com/forums/topic/177286-any-interest-in-nes-rob-homebrews/),
as well as
[Anne Barela's work](https://learn.adafruit.com/controlling-a-classic-nintendo-r-o-b-robot-using-circuit-playground-express/overview)
at Adafruit.

The NesRob library simplies the interaction with the NES R.O.B. by handling the
precision timing and command processing necessary to control R.O.B. The end user
can simply choose an LED pin, then supply any of R.O.B.'s available actions to
invoke the specified behavior in R.O.B. This library operates on top of the
Arduino API, and therefore should be available to any Arduino compatible device.

To use this library:

```c++
#include <NesRob.h>

NesRob rob;

void setup() { }

void loop() {
  rob.blinkCommand(NesRob::Command::HANDS_CLOSE);
  delay(1000);
}
```

[API Documentation](api.md)
---------------------------

_Click the title to view the API documentation page._

Examples
--------

* [CloseHands](https://www.github.com/zfields/nes-rob/tree/main/examples/CloseHands/CloseHands.ino):
Validate your hardware configuration by sending a simple command to R.O.B.
