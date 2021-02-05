#include "signal_generator.hpp"

#include "pulse_driver.hpp"

SignalGenerator::SignalGenerator (
    PulseDriver * driver_
) :
    _driver(driver_)
{ }

int
SignalGenerator::init (
    void * params_
) {
    ErrorCode result;

    (void)params_;  // ignore parameters

    if (_driver->init(nullptr)) {
        result = ErrorCode::E_DRIVER;
    } else {
        result = ErrorCode::SUCCESS;
    }

    return static_cast<int>(result);
}

int
SignalGenerator::signal (
    int sequence_
) const {
    ErrorCode result;
    const unsigned int preamble[] = {0,0,0,0,1,0};
    bool halt = false;

    // Pulse initialization sequence
    for (unsigned int i = 0 ; i < (sizeof(preamble)/sizeof(unsigned int)) ; ++i) {
        if (_driver->pulse(preamble[i])) {
            result = ErrorCode::E_DRIVER;
            halt = true;
            break;
        }
    }

    if (!halt) {
        // Pulse sequence
        for (int i = 7 ; i >= 0 ; --i) {
            unsigned int active = ((static_cast<unsigned int>(sequence_) >> i) & static_cast<unsigned int>(0x1));
            if (_driver->pulse(active)) {
                result = ErrorCode::E_DRIVER;
                break;
            }
            result = ErrorCode::SUCCESS;
        }
    }

    return static_cast<int>(result);
}

int
SignalGenerator::testSignal (
    void
) const {
    ErrorCode result;

    const unsigned int test_signal[] = {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0};

    // Test signal sequence
    for (unsigned int i = 0 ; i < (sizeof(test_signal)/sizeof(unsigned int)) ; ++i) {
        if (_driver->pulse(test_signal[i])) {
            result = ErrorCode::E_DRIVER;
            break;
        }
        result = ErrorCode::SUCCESS;
    }

    return static_cast<int>(result);
}
