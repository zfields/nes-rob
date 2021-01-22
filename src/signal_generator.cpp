#include "signal_generator.hpp"

#include "signal_driver.hpp"

SignalGenerator::SignalGenerator (
    const SignalDriver * driver_
) :
    _driver(driver_)
{ }

int
SignalGenerator::signal (
    int command_sequence_
) const {
    // Send initialization sequence
    _driver->pulse(0);
    _driver->pulse(0);
    _driver->pulse(0);
    _driver->pulse(1);
    _driver->pulse(0);

    // Flash command sequence
    for (int i = 7 ; i >= 0 ; --i) {
        unsigned int active = ((static_cast<unsigned int>(command_sequence_) >> i) & static_cast<unsigned int>(0x1));
        _driver->pulse(active);
    }

    return 0;
}
