#include "signal_generator.hpp"

#include "pulse_driver.hpp"
#include "signal_generator_error.hpp"

using namespace nes::rob;

SignalGenerator::SignalGenerator (
    PulseDriver * driver_
) :
    _driver(driver_)
{ }

nes::rob::error_code
SignalGenerator::init (
    void * reserved_
) {
    nes::rob::error_code result;

    (void)reserved_;  // ignore parameters

    if (_driver->init(nullptr)) {
        result = make_error_code(signal_generator_error::driver_init);
    } else {
        result = make_error_code(signal_generator_error::success);
    }

    return result;
}

nes::rob::error_code
SignalGenerator::signal (
    int sequence_
) const {
    nes::rob::error_code result;
    const unsigned int preamble[] = {0,0,0,0,1,0};
    bool halt = false;

    // Pulse initialization sequence
    for (unsigned int i = 0 ; i < (sizeof(preamble)/sizeof(unsigned int)) ; ++i) {
        if (preamble[i] ? _driver->pulse() : _driver->rest()) {
            result = make_error_code(signal_generator_error::driver_error);
            halt = true;
            break;
        }
    }

    if (!halt) {
        // Pulse sequence
        for (int i = 7 ; i >= 0 ; --i) {
            unsigned int pulse = ((static_cast<unsigned int>(sequence_) >> i) & static_cast<unsigned int>(0x1));
            if (pulse ? _driver->pulse() : _driver->rest()) {
                result = make_error_code(signal_generator_error::driver_error);
                break;
            }
            result = make_error_code(signal_generator_error::success);
        }
    }

    return result;
}

nes::rob::error_code
SignalGenerator::testSignal (
    void
) const {
    nes::rob::error_code result;

    const unsigned int test_signal[] = {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0};

    // Test signal sequence
    for (unsigned int i = 0 ; i < (sizeof(test_signal)/sizeof(unsigned int)) ; ++i) {
        if (test_signal[i] ? _driver->pulse() : _driver->rest()) {
            result = make_error_code(signal_generator_error::driver_error);
            break;
        }
        result = make_error_code(signal_generator_error::success);
    }

    return result;
}
