NES R.O.B. Control Library
==========================

This library allows an Arduino board to control the Nintendo Entertainment
System Robotic Operating Buddy (R.O.B.). The hardware configuration needed to
control R.O.B. requires the placement of an LED in front of the left eye. The
LED should be controlled by the microcontroller using this library.

![Gyromite Manual Depiction of NES R.O.B.](img/nes-rob.png)

The `NesRob` library simplies the interaction with the NES R.O.B., by handling
the precision timing and command processing necessary to control R.O.B. The end
user can simply choose an LED pin, then supply any of R.O.B.'s available actions
to invoke the specified behavior in R.O.B. This library operates on top of the
Arduino API, and therefore should be available to any Arduino compatible device.

To use this library:

```c++
#include <NesRob.h>

NesRob rob;

void setup() { }

void loop() {
  rob.sendCommand(NesRob::Command::CLOSE);
  delay(1000);
}
```

> _**NOTE:** This library borrows the research done by `x87bliss` along with
> those on the
> [Atari Age Forums](https://atariage.com/forums/topic/177286-any-interest-in-nes-rob-homebrews/),
> as well as
> [Anne Barela's guide](https://learn.adafruit.com/controlling-a-classic-nintendo-r-o-b-robot-using-circuit-playground-express/overview)
> at Adafruit._

API Documentation
-----------------

_[Click here](api.md) to view the API documentation page._

Examples
--------

* [Blink](https://www.github.com/zfields/nes-rob/tree/main/examples/Blink/Blink.ino):
Validate your hardware configuration by flashing the LED on R.O.B.'s head.

* [Close](https://www.github.com/zfields/nes-rob/tree/main/examples/Close/Close.ino):
Validate your hardware configuration by sending a simple command to R.O.B.

* [Stow](https://www.github.com/zfields/nes-rob/tree/main/examples/Stow/Stow.ino):
Put R.O.B. into the position required to fit the original packaging.

* [StowDirect](https://www.github.com/zfields/nes-rob/tree/main/examples/StowDirect/StowDirect.ino):
Use interrupts to control R.O.B. and ready him for the original packaging.

Research
--------

_[Click here](research.md) to view the research page._
