/*
  Prepare R.O.B. for storage in his original packaging

  Utilizes a direct connection to the motherboard connector (which typically
  joins the head and base) to send control signals to the main CPU. When the
  signal is received by the main CPU, R.O.B. will await the initialization
  sequence and execute the routine to return to the position required to fit
  inside the styrofoam mold of the original packaging.

  This sketch operates in direct mode, meaning the hardware was modified to
  provide direct access to the main CPU. As such, it relies on the status of
  the LED line to know when R.O.B. has finished executing each command, before
  submitting any subsequent commands. R.O.B.'s response validates your hardware
  configuration.

  The circuit:

  | Connector |   Arduino   |                                                  |
  |   Label   |     Pin     | Description                                      |
  |:---------:|:-----------:|:-------------------------------------------------|
  |    `G`    |    `GND`    | Requires common ground reference to sink voltage.|
  |    `S`    |`LED_BUILTIN`| Connect to the ~6V signal line.                  |
  |    `L`    |     `A0`    | Sample to the ~2V LED line.                      |
  |    `V`    |    `Vin`    | [Optional] Provide power to your 5V Arduino.     |

  *************************
  * NOTE: This sample was created for the Arduino UNO, please consider any and
  *       all electrical specifications and limitations of your board before
  *       wiring the circuit.
  *************************

  *************************
  * WARNING: This typically requires a 5V compatible Arduino microcontroller. If
  *          a 3V (or less) microcontroller is used, you MUST use a level
  *          shifter to signal R.O.B. and do NOT connect to `V`.
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
  rob.sendCommand(NesRob::Command::LOWER_2);
  do {
    ::delay(SAMPLE_DELAY);
  } while(::analogRead(A0) < EPSILON);

  rob.sendCommand(NesRob::Command::LOWER_2);
  do {
    ::delay(SAMPLE_DELAY);
  } while(::analogRead(A0) < EPSILON);

  rob.sendCommand(NesRob::Command::LOWER);
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
