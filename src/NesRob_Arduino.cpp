#include "NesRob.h"

#include "hal_arduino.hpp"
#include "led_ntsc_driver.hpp"
#include "signal_generator.hpp"

NesRob::NesRob (
    unsigned int pin_
) :
    _hal(new HalArduino()),
    _pulse_driver(new LedNtscDriver(_hal, pin_)),
    _signal_generator(new SignalGenerator(_pulse_driver))
{
    _signal_generator->init(nullptr);
}

NesRob::~NesRob (
    void
) {
    delete _hal;
    delete _pulse_driver;
    delete _signal_generator;
}

int
NesRob::begin (
    void * params_
) {
    return _signal_generator->init(nullptr);
}

void
NesRob::blinkCommand (
    Command command_
) const {
    _signal_generator->signal(static_cast<int>(command_));
}

int
NesRob::sendCommand (
    Command command_
) const {
    ErrorCode result;

    if (_signal_generator->signal(static_cast<int>(command_))) {
        result = ErrorCode::E_SIGGEN;
    } else {
        result = ErrorCode::SUCCESS;
    }

    return static_cast<int>(result);
}
