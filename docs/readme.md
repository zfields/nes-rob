NES R.O.B. Control Library
==========================

This library allows an Arduino board to control the Nintendo Entertainment
System Robot Operating Buddy (R.O.B.). The hardware configuration needed to
control R.O.B. requires the placement of an LED in front of the left eye. The
LED should be controlled by the microcontroller using this library.

The `NesRob` library simplies the interaction with the NES R.O.B., by handling
the precision timing and command processing necessary to control R.O.B. The end
user can simply choose an LED pin, then supply any of R.O.B.'s available actions
to invoke the specified behavior in R.O.B. This library operates on top of the
Arduino API, and therefore should be available to any Arduino compatible device.

To use this library:

```c++
#include <NesRob.h>

NesRob rob;

void setup() {
  rob.begin();
}

void loop() {
  rob.sendCommand(NesRob::Command::ARMS_CLOSE);
  delay(1000);
}
```

> _**NOTE:** This library borrows the research done by `x87bliss` along with
> those on the
> [Atari Age Forums](https://atariage.com/forums/topic/177286-any-interest-in-nes-rob-homebrews/),
> as well as
> [Anne Barela's guide](https://learn.adafruit.com/controlling-a-classic-nintendo-r-o-b-robot-using-circuit-playground-express/overview)
> at Adafruit._

[API Documentation](api.md)
---------------------------

_Click the title to view the API documentation page._

Examples
--------

* [CloseArms](https://www.github.com/zfields/nes-rob/tree/main/examples/CloseArms/CloseArms.ino):
Validate your hardware configuration by sending a simple command to R.O.B.

[Research](research.md)
-----------------------

_Click the title to view the research page._
