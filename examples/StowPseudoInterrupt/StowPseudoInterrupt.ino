/*
  Prepare R.O.B. for storage in his original packaging

  First, the sketch awaits the execution start-up calibration routine.
  Then the subsequent commands return R.O.B. to the position required to fit in
  the styrofoam mold of the original packaging.

  Unlike the other sketch, which relies on timing delays to know when R.O.B. has
  finished executing any previous commands before submitting new commands. This
  sketch operates on a pseudo-interrupt, to know when R.O.B. is ready to receive
  the next command. In order to unlock this capability, the hardware was
  modified in order to provide direct access to the main CPU. A detailed
  decription of this modification can be viewed on the Hackster project page,
  https://www.hackster.io/zachary_fields/cellular-r-o-b-with-blues-wireless-38ac41

  Now, the MCU can rely on the status of the LED line to know when R.O.B. has
  finished executing a command. This provides for improved performance when
  coordinated, or chained, commands are required to execute a given task.

  The circuit:

  | Connector |   Arduino   |                                                  |
  |   Label   |     Pin     | Description                                      |
  |:---------:|:-----------:|:-------------------------------------------------|
  |    `G`    |    `GND`    | Requires common ground reference to sink voltage.|
  |    `S`    |`LED_BUILTIN`| Connect to the ~6V signal line.                  |
  |    `L`    |     `A0`    | Sample to the ~2V LED line.                      |
  |    `V`    |    `Vin`    | [Optional] Provide power to your 5V Arduino.     |

  *************************
  * NOTE: The interrupt signal cannot be captured natively, because the voltage
  *       (2V) is too low. Therefore, this sketch uses `analogRead()` to sample
  *       the voltage on `L`, as a pseudo-interrupt. In order to use standard
  *       interrupt handling techniques, a level shifter is required.
  *************************

  *************************
  * NOTE: This sample was created specifically for the Arduino Uno. Please
  *       consider any and all electrical specifications and limitations of your
  *       board before attempting to replicate the circuit.
  *************************

  *************************
  * WARNING: This circuit requires a 5V compatible Arduino microcontroller. If
  *          a 3V (or less) microcontroller is used, you MUST use a level
  *          shifter to signal R.O.B. DO NOT provide power to your MCU from `V`
  *          directly.
  *************************

  created 2021
  by Zachary J. Fields

  This example code is in the public domain.
  http://www.github.com/zfields/nes-rob
*/

#include "NesRob.h"

static const int EPSILON = 100;
static const int SAMPLE_DELAY = 50;

NesRob rob(LED_BUILTIN, NesRob::CommandTarget::MAIN_CPU);

void setup() {
  // Wait for R.O.B. to execute start-up calibration sequence
  do {
    ::delay(SAMPLE_DELAY);
    rob.sendCommand(NesRob::Command::LED_ENABLE);
  } while(::analogRead(A0) < EPSILON);

  // Execute stow routine
  rob.sendCommand(NesRob::Command::DOWN_2);
  do {
    ::delay(SAMPLE_DELAY);
  } while(::analogRead(A0) < EPSILON);

  rob.sendCommand(NesRob::Command::DOWN_2);
  do {
    ::delay(SAMPLE_DELAY);
  } while(::analogRead(A0) < EPSILON);

  rob.sendCommand(NesRob::Command::DOWN);
  do {
    ::delay(SAMPLE_DELAY);
  } while(::analogRead(A0) < EPSILON);

  rob.sendCommand(NesRob::Command::CLOSE);
  do {
    ::delay(SAMPLE_DELAY);
  } while(::analogRead(A0) < EPSILON);
}

void loop() {
  // put your main code here, to run repeatedly:

}
