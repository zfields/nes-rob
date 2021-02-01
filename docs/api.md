NesRob Library
==============

Definitions
-----------

### `Command` (enum class)

The `Command` enum class specifies which movements are available to R.O.B.

Command List:

- `CALIBRATE_MOTORS`

  Runs the startup calibration routine.

- `LED_DISABLE`

  Disables the LED on top of R.O.B.'s head.

  > _**NOTE:** Not idempotent. Enables LED to disable, if previously disabled._

- `LED_ENABLE`

  Enables the LED on top of R.O.B.'s head.

- `TEST_LED` **[Deprecated]**

  Turns on the LED on top of R.O.B.'s head.

  > _**WARNING:** This API was deprecated in v1.1.0, and is no longer supported._

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

- `HANDS_CLOSE` **[Deprecated]**

  Brings R.O.B.'s hands together.

  > _**WARNING:** This API was deprecated in v1.1.0, and is no longer supported._

- `ARMS_OPEN`

  Spreads R.O.B.'s arms apart.

- `HANDS_OPEN` **[Deprecated]**

  Spreads R.O.B.'s hands apart.

  > _**WARNING:** This API was deprecated in v1.1.0, and is no longer supported._

### `CommandTarget` (enum class)

The `CommandTarget` enum class specifies which targets are available to R.O.B.
to receive [`Commands`](#command-enum-class).

CommandTarget List:

- `PHOTOSENSOR`

  Targets the photosensor in R.O.B.'s left eye, by flashing an LED in accordance
  with the NTSC standard.

- `MAIN_CPU`

  Targets the Main CPU on R.O.B.'s motherboard. Generates a signal, using the
  same square wave transform as the optical electronics in R.O.B. head.

  > _**NOTE:**  This requires hardware modification to utilize. The signal
  > should be injected inline with the ribbon cable, running down R.O.B.'s neck
  > from his head to the base._

### `ErrorCode` (enum class)

The `ErrorCode` enum class identifies the error codes returned by the `NesRob`
library implementation.

ErrorCode List:

- `SUCCESS`

  The command executed as expected.

- `E_SIGGEN`

  An error occured during signal generation.

Methods
-------

### `NesRob` _(constructor)_

Requires a pin number argument to creates the NesRob instance.

**Signature:**

```cpp
NesRob::NesRob(unsigned int, NesRob::CommandTarget);
```

**Parameters:**

- _pin_: the pin used to drive the LED
- _target_: the target for generated instructions [**default:**
`NesRob::CommandTarget::PHOTOSENSOR`]

**Example:**

```cpp
#include <NesRob.h>

NesRob rob(LED_BUILTIN, NesRob::CommandTarget::PHOTOSENSOR);
```

### `blinkCommand` [deprecated]

Manipulates R.O.B. by blinking the signal related to the `Command` provided to
the API.

**Signature:**

```cpp
void NesRob::blinkCommand(NesRob::Command);
```

**Parameters:**

- _command_: a bit array used to indicate the flash pattern

> _**WARNING:** This API was deprecated in v1.1.0, and is no longer supported._

**Returns:**

Nothing

**See also:**

- [`sendCommand`](#sendcommand)

### `sendCommand`

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

- `ErrorCode::SUCCESS` (`0`) - The command executed as expected.
- `ErrorCode::E_SIGGEN` - Signal generator failed unexpectedly.

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
