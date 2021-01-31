#include "arduino_debug_driver.hpp"

#include <Arduino.h>

#include "hardware_abstraction_layer.hpp"

//TODO: Abstract this from Arduino
int
ArduinoDebugDriver::init (
    void * params_
) {
    (void)params_; // ignore parameter

    // Initialize Debug Output
    Serial.begin(115200);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB
    }

    // Print parameter constant values
    Serial.print("PIN_MODE_INPUT: ");
    Serial.println(HardwareAbstractionLayer::PIN_MODE_INPUT, DEC);
    Serial.print("PIN_MODE_INPUT_PULLUP: ");
    Serial.println(HardwareAbstractionLayer::PIN_MODE_INPUT_PULLUP, DEC);
    Serial.print("PIN_MODE_OUTPUT: ");
    Serial.println(HardwareAbstractionLayer::PIN_MODE_OUTPUT, DEC);
    Serial.print("PIN_STATE_HIGH: ");
    Serial.println(HardwareAbstractionLayer::PIN_STATE_HIGH, DEC);
    Serial.print("PIN_STATE_LOW: ");
    Serial.println(HardwareAbstractionLayer::PIN_STATE_LOW, DEC);

    return static_cast<int>(ErrorCode::SUCCESS);
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
    return static_cast<int>(ErrorCode::SUCCESS);
}