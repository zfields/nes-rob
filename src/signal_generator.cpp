#include "signal_generator.hpp"

#include "signal_driver.hpp"

SignalGenerator::SignalGenerator (
    const SignalDriver * driver_
) :
    _driver(driver_)
{ }

int
SignalGenerator::signal (
    int sequence_
) const {
    int result = 0;
    const unsigned int preamble[] = {0,0,0,1,0};

    // Pulse initialization sequence
    for (unsigned int i = 0 ; i < (sizeof(preamble)/sizeof(unsigned int)) ; ++i) {
        if ((result = _driver->pulse(preamble[i]))) { break; }
    }

    // Pulse sequence
    for (int i = 7 ; i >= 0 && !result ; --i) {
        unsigned int active = ((static_cast<unsigned int>(sequence_) >> i) & static_cast<unsigned int>(0x1));
        if ((result = _driver->pulse(active))) { break; }
    }

    return result;
}
