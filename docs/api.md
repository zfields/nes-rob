NesRob Library
==============

Definitions
-----------

### `Command` (enum class)

The `Command` enum class specified which movements are available to R.O.B.

Command List:

- `CALIBRATE_MOTORS`

  Runs the startup calibration routine.

- `TEST_LED`

  Turns on the LED on top of R.O.B.'s head.

- `ARMS_LEFT`

  Turn R.O.B.'s torso to the left one station [1,5].

- `ARMS_RIGHT`

  Turn R.O.B.'s torso to the right one station [1,5].

- `ARMS_LOWER`

  Lower R.O.B.'s arms one notch (on back of spine) [1,6].

- `ARMS_LOWER_2`

  Lower R.O.B.'s arms two notches (on back of spine) [1,6].

- `ARMS_RAISE`

  Raise R.O.B.'s arms one notch (on back of spine) [1,6].

- `ARMS_RAISE_2`

  Raise R.O.B.'s arms two notches (on back of spine) [1,6].

- `HANDS_CLOSE`

  Brings R.O.B.'s hands together.

- `HANDS_OPEN`

  Spreads R.O.B.'s hands apart.

Methods
-------

### `NesRob(unsigned int)` (constructor)

Requires a pin number argument to creates the NesRob instance.

#### Syntax

```
NesRob rob(13);
```

#### Parameters

* _pin_: the pin used to drive the LED

#### Example

```c++
#include <NesRob.h>

NesRob rob;
```
### `blinkCommand(Command)`

Manipulates R.O.B. by blinking the signal related to the `Command` provided to
the API.

#### Syntax

```
rob.blinkCommand(NesRob::Command::HANDS_CLOSE);
```

#### Parameters

* _command_: a bit array used to indicate the flash pattern

#### Example

```c++
#include <NesRob.h>

NesRob rob;

void setup() { }

void loop() {
  rob.blinkCommand(NesRob::Command::HANDS_CLOSE);
  delay(1000);
}
```

#### See also

* [`Command` enum class](#command-enum-class)