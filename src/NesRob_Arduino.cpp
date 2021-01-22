#include "NesRob.h"

#include "hal_arduino.hpp"
#include "led_ntsc_driver.hpp"
#include "signal_generator.hpp"

NesRob::NesRob (
    unsigned int pin_
) :
    _hal_clock(new HalArduino()),
    _hal_gpio(reinterpret_cast<const HalArduino *>(_hal_clock)),
    _sig_drv(new LedNtscDriver(_hal_clock, _hal_gpio, pin_)),
    _sig_gen(new SignalGenerator(_sig_drv))
{ }

NesRob::~NesRob (
    void
) {
    delete reinterpret_cast<const HalArduino *>(_hal_clock);
    delete _sig_drv;
    delete _sig_gen;
}

void
NesRob::blinkCommand (
    Command command_
) {
    _sig_gen->signal(static_cast<int>(command_));
}
