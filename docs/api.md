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

- `ARMS_CLOSE`

  Brings R.O.B.'s arms together.

- `HANDS_CLOSE` [Deprecated]

  Brings R.O.B.'s hands together.

- `ARMS_OPEN`

  Spreads R.O.B.'s arms apart.

- `HANDS_OPEN` [Deprecated]

  Spreads R.O.B.'s hands apart.

Methods
-------

### `NesRob(unsigned int)` (constructor)

Requires a pin number argument to creates the NesRob instance.

**Signature:**

```cpp
NesRob::NesRob(unsigned int);
```

**Parameters:**

- _pin_: the pin used to drive the LED

**Example:**

```cpp
#include <NesRob.h>

NesRob rob;
```

### `blinkCommand(Command)` [deprecated]

Manipulates R.O.B. by blinking the signal related to the `Command` provided to
the API.

**Signature:**

```cpp
void NesRob::blinkCommand(NesRob::Command);
```

**Parameters:**

- _command_: a bit array used to indicate the flash pattern

> _**NOTE:** This API was deprecated in v1.1.0, and is no longer supported._

**Returns:**

Nothing

**See also:**

- [`sendCommand`](#sendcommand\(command\))

### `sendCommand(Command)`

Manipulates R.O.B. by blinking the signal related to the `Command` provided to
the API.

**Signature:**

```cpp
int NesRob::sendCommand(NesRob::Command);
```

**Parameters:**

- _command_: a bit array used to indicate the flash pattern

**Returns:**

An `int`, describing the result of the command.

- `0` - Success: The command executed as expected.

**Example:**

```cpp
#include <NesRob.h>

NesRob rob;

void setup() { }

void loop() {
  rob.sendCommand(NesRob::Command::ARMS_CLOSE);
  delay(1000);
}
```

**See also:**

- [`Command` enum class](#command-enum-class)
