#include "arduino_debug_driver.hpp"

#include <Arduino.h>
#include "hal_gpio.hpp"

ArduinoDebugDriver::ArduinoDebugDriver (
    void
) {
    // Initialize Debug Output
    Serial.begin(115200);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB
    }

    Serial.print("PIN_MODE_INPUT: ");
    Serial.println(HalGpio::PIN_MODE_INPUT, DEC);
    Serial.print("PIN_MODE_INPUT_PULLUP: ");
    Serial.println(HalGpio::PIN_MODE_INPUT_PULLUP, DEC);
    Serial.print("PIN_MODE_OUTPUT: ");
    Serial.println(HalGpio::PIN_MODE_OUTPUT, DEC);
    Serial.print("PIN_STATE_HIGH: ");
    Serial.println(HalGpio::PIN_STATE_HIGH, DEC);
    Serial.print("PIN_STATE_LOW: ");
    Serial.println(HalGpio::PIN_STATE_LOW, DEC);
}

int
ArduinoDebugDriver::pulse (
    unsigned int active_
) const {
    if (active_) {
        Serial.println("ACTIVE");
    } else {
        Serial.println("passive");
    }
    return 0;
}
