#include "NesRob.h"

#include "hal_arduino.hpp"
#include "led_ntsc_driver.hpp"
#include "signal_generator.hpp"
#include "w_wave_driver.hpp"

using namespace nes::rob;

NesRob::NesRob (
    unsigned int pin_,
    CommandTarget target_
) :
    _hal(new HalArduino()),
    _pulse_driver(CommandTarget::PHOTOSENSOR == target_
        ? reinterpret_cast<PulseDriver *>(new LedNtscDriver(_hal, pin_))
        : reinterpret_cast<PulseDriver *>(new WWaveDriver(_hal, pin_))
    ),
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

void
NesRob::blinkCommand (
    Command command_
) const {
    sendCommand(command_);
}

int
NesRob::sendCommand (
    Command command_
) const {
    ErrorCode result;
    if ((Command::LED_DISABLE == command_)
        ? _signal_generator->testSignal()
        : _signal_generator->signal(static_cast<int>(command_))
    ) {
        result = ErrorCode::E_SIGGEN;
    } else {
        result = ErrorCode::SUCCESS;
    }

    return static_cast<int>(result);
}
