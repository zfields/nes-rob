#ifndef RUN_ALL_TESTS
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#endif

#include <catch2/catch.hpp>
#include <fakeit.hpp>

// Compile Command: g++ w_wave_driver.test.cpp ../src/w_wave_driver.cpp ../src/hal_error.cpp ../src/pulse_driver_error.cpp -Wall -Wpedantic -I ../src/ -I Catch2/single_include/ -I FakeIt/single_header/catch/

#include "hal_error.hpp"
#include "hardware_abstraction_layer.hpp"
#include "pulse_driver_error.hpp"
#include "w_wave_driver.hpp"

__attribute__((weak)) const int HardwareAbstractionLayer::PIN_STATE_HIGH = 10;
__attribute__((weak)) const int HardwareAbstractionLayer::PIN_MODE_INPUT = 20;
__attribute__((weak)) const int HardwareAbstractionLayer::PIN_MODE_INPUT_PULLUP = 30;
__attribute__((weak)) const int HardwareAbstractionLayer::PIN_STATE_LOW = 40;
__attribute__((weak)) const int HardwareAbstractionLayer::PIN_MODE_OUTPUT = 50;

TEST_CASE("HardwareAbstractionLayer::init() is invoked during WWaveDriver::init()", "[init][hal]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,init)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::Fake(Method(mock_hal,pinMode));
    WWaveDriver w_wave_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    w_wave_driver.init(nullptr);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,init)).Once();
    CHECK(true);
}

TEST_CASE("Pin provided to WWaveDriver() is set to HardwareAbstractionLayer::PIN_MODE_INPUT during WWaveDriver::init()", "[constructor][init][hal][pin_mode]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::Fake(Method(mock_hal,init));
    fakeit::When(Method(mock_hal,pinMode)).AlwaysReturn(nes::rob::hal_error::success);
    WWaveDriver w_wave_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    w_wave_driver.init(nullptr);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,pinMode)).Once();
    fakeit::Verify(Method(mock_hal,pinMode).Using(TEST_PIN, HardwareAbstractionLayer::PIN_MODE_INPUT));
    CHECK(true);
}

TEST_CASE("WWaveDriver::init() returns `pulse_driver_error::hal_init`, when HardwareAbstractionLayer::init() returns an error", "[init][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,init)).AlwaysReturn(nes::rob::hal_error::sys_config);
    fakeit::When(Method(mock_hal,pinMode)).AlwaysReturn(nes::rob::hal_error::success);
    WWaveDriver w_wave_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const std::error_code result = w_wave_driver.init(nullptr);

    // Evalulate Result
    CHECK(nes::rob::pulse_driver_error::hal_init == result);
}

TEST_CASE("WWaveDriver::init() will stop processing if HardwareAbstractionLayer::init() returns an error", "[init][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,init)).AlwaysReturn(nes::rob::hal_error::sys_config);
    fakeit::When(Method(mock_hal,pinMode)).AlwaysReturn(nes::rob::hal_error::success);
    WWaveDriver w_wave_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    w_wave_driver.init(nullptr);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,init)).Once();
    fakeit::VerifyNoOtherInvocations(mock_hal);
    CHECK(true);
}

TEST_CASE("WWaveDriver::init() returns `pulse_driver_error::hal_gpio_config`, when pinMode() returns an error", "[init][hal][pin_mode][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,init)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,pinMode)).AlwaysReturn(nes::rob::hal_error::peripheral_gpio);
    WWaveDriver w_wave_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const std::error_code result = w_wave_driver.init(nullptr);

    // Evalulate Result
    CHECK(nes::rob::pulse_driver_error::hal_gpio_config == result);
}

TEST_CASE("WWaveDriver::init() will stop processing if pinMode() returns an error", "[init][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,init)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,pinMode)).AlwaysReturn(nes::rob::hal_error::peripheral_gpio);
    WWaveDriver w_wave_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    w_wave_driver.init(nullptr);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,init) + Method(mock_hal,pinMode)).Once();
    fakeit::VerifyNoOtherInvocations(mock_hal);
    CHECK(true);
}

TEST_CASE("WWaveDriver::init() returns `pulse_driver_error::success`, when no errors occur", "[init][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,init)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,pinMode)).AlwaysReturn(nes::rob::hal_error::success);
    WWaveDriver w_wave_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const std::error_code result = w_wave_driver.init(nullptr);

    // Evalulate Result
    CHECK(nes::rob::pulse_driver_error::success == result);
}

TEST_CASE("WWaveDriver::pulse() generates well-formed W square wave (pulse) when called with a non-zero value", "[pulse][active][hal][pin_state]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,pinMode)).AlwaysReturn(nes::rob::hal_error::success);
    WWaveDriver w_wave_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    w_wave_driver.pulse(!0);

    // Evalulate Result
    // Required to verify NO OTHER CALLS to these APIs are made (could be checked by supplying a specific list of return values)
    fakeit::Verify(Method(mock_hal,pinMode) + Method(mock_hal,digitalWrite) + Method(mock_hal,delayMicroseconds) + Method(mock_hal,pinMode) + Method(mock_hal,delayMicroseconds) + Method(mock_hal,pinMode) + Method(mock_hal,digitalWrite) + Method(mock_hal,delayMicroseconds) + Method(mock_hal,pinMode) + Method(mock_hal,delayMicroseconds)).Once();
    // Specific execution (does not guarantee that no other calls are made before and/or after even when supplied with the once command)
    fakeit::Verify(Method(mock_hal,pinMode).Using(fakeit::_, HardwareAbstractionLayer::PIN_MODE_OUTPUT) + Method(mock_hal,digitalWrite).Using(fakeit::_, HardwareAbstractionLayer::PIN_STATE_LOW) + Method(mock_hal,delayMicroseconds).Using(796) + Method(mock_hal,pinMode).Using(fakeit::_, HardwareAbstractionLayer::PIN_MODE_INPUT) + Method(mock_hal,delayMicroseconds).Using(730) + Method(mock_hal,pinMode).Using(fakeit::_, HardwareAbstractionLayer::PIN_MODE_OUTPUT) + Method(mock_hal,digitalWrite).Using(fakeit::_, HardwareAbstractionLayer::PIN_STATE_LOW) + Method(mock_hal,delayMicroseconds).Using(796) + Method(mock_hal,pinMode).Using(fakeit::_, HardwareAbstractionLayer::PIN_MODE_INPUT) + Method(mock_hal,delayMicroseconds).Using(14330));
    CHECK(true);
}

TEST_CASE("WWaveDriver::pulse() omits pulse for fixed time period, when called with a zero value", "[pulse][hal][pin_state]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,pinMode)).AlwaysReturn(nes::rob::hal_error::success);
    WWaveDriver w_wave_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    w_wave_driver.pulse(0);

    // Evalulate Result
    // Required to verify NO OTHER CALLS to these APIs are made (could be checked by supplying a specific list of return values)
    fakeit::Verify(Method(mock_hal,pinMode) + Method(mock_hal,delayMicroseconds)).Once();
    // Specific execution (does not guarantee that no other calls are made before and/or after even when supplied with the once command)
    fakeit::Verify(Method(mock_hal,pinMode).Using(fakeit::_, HardwareAbstractionLayer::PIN_MODE_INPUT) + Method(mock_hal,delayMicroseconds).Using(16663));
    CHECK(true);
}

TEST_CASE("Pin provided to WWaveDriver() is supplied to HAL interface when WWaveDriver::pulse() is called with a non-zero value", "[constructor][pulse][active][hal]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::Fake(Method(mock_hal,delayMicroseconds));
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,pinMode)).AlwaysReturn(nes::rob::hal_error::success);
    WWaveDriver w_wave_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    w_wave_driver.pulse(!0);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,pinMode).Using(TEST_PIN, fakeit::_));
    fakeit::Verify(Method(mock_hal,digitalWrite).Using(TEST_PIN, fakeit::_));
    CHECK(true);
}

TEST_CASE("Pin provided to WWaveDriver() is supplied to HAL interface when WWaveDriver::pulse() is called with a zero value", "[constructor][pulse][hal]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::Fake(Method(mock_hal,delayMicroseconds));
    fakeit::When(Method(mock_hal,pinMode)).AlwaysReturn(nes::rob::hal_error::success);
    WWaveDriver w_wave_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    w_wave_driver.pulse(0);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,pinMode).Using(TEST_PIN, fakeit::_));
    CHECK(true);
}

TEST_CASE("WWaveDriver::pulse() called with a non-zero value, returns `pulse_driver_error::hal_gpio_config`, when first invocation of pinMode() returns an error", "[pulse][active][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::Fake(Method(mock_hal,delayMicroseconds));
    fakeit::Fake(Method(mock_hal,digitalWrite));
    fakeit::When(Method(mock_hal,pinMode)).Return(
        nes::rob::hal_error::peripheral_gpio,
        nes::rob::hal_error::success,
        nes::rob::hal_error::success,
        nes::rob::hal_error::success
    );
    WWaveDriver w_wave_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const std::error_code result = w_wave_driver.pulse(!0);

    // Evalulate Result
    CHECK(nes::rob::pulse_driver_error::hal_gpio_config == result);
}

TEST_CASE("WWaveDriver::pulse() called with a non-zero value, will stop processing if the first invocation of pinMode() returns an error", "[pulse][active][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::Fake(Method(mock_hal,delayMicroseconds));
    fakeit::Fake(Method(mock_hal,digitalWrite));
    fakeit::When(Method(mock_hal,pinMode)).Return(
        nes::rob::hal_error::peripheral_gpio,
        nes::rob::hal_error::success,
        nes::rob::hal_error::success,
        nes::rob::hal_error::success
    );
    WWaveDriver w_wave_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    w_wave_driver.pulse(!0);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,pinMode)).Once();
    fakeit::VerifyNoOtherInvocations(mock_hal);
    CHECK(true);
}

TEST_CASE("WWaveDriver::pulse() called with a non-zero value, returns `pulse_driver_error::hal_gpio_state`, when first invocation of digitalWrite() returns an error", "[pulse][active][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::Fake(Method(mock_hal,delayMicroseconds));
    fakeit::When(Method(mock_hal,digitalWrite)).Return(
        nes::rob::hal_error::peripheral_gpio,
        nes::rob::hal_error::success
    );
    fakeit::Fake(Method(mock_hal,pinMode));
    WWaveDriver w_wave_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const std::error_code result = w_wave_driver.pulse(!0);

    // Evalulate Result
    CHECK(nes::rob::pulse_driver_error::hal_gpio_state == result);
}

TEST_CASE("WWaveDriver::pulse() called with a non-zero value, will stop processing if the first invocation of digitalWrite() returns an error", "[pulse][active][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::Fake(Method(mock_hal,delayMicroseconds));
    fakeit::When(Method(mock_hal,digitalWrite)).Return(
        nes::rob::hal_error::peripheral_gpio,
        nes::rob::hal_error::success
    );
    fakeit::Fake(Method(mock_hal,pinMode));
    WWaveDriver w_wave_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    w_wave_driver.pulse(!0);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,pinMode) + Method(mock_hal,digitalWrite)).Once();
    fakeit::VerifyNoOtherInvocations(mock_hal);
    CHECK(true);
}

TEST_CASE("WWaveDriver::pulse() called with a non-zero value, returns `pulse_driver_error::hal_clock`, when first invocation of delayMicroseconds() returns an error", "[pulse][active][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).Return(
        nes::rob::hal_error::sys_clock,
        nes::rob::hal_error::success,
        nes::rob::hal_error::success,
        nes::rob::hal_error::success
    );
    fakeit::Fake(Method(mock_hal,digitalWrite));
    fakeit::Fake(Method(mock_hal,pinMode));
    WWaveDriver w_wave_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const std::error_code result = w_wave_driver.pulse(!0);

    // Evalulate Result
    CHECK(nes::rob::pulse_driver_error::hal_clock == result);
}

TEST_CASE("WWaveDriver::pulse() called with a non-zero value, will stop processing if the first invocation of delayMicroseconds() returns an error", "[pulse][active][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).Return(
        nes::rob::hal_error::sys_clock,
        nes::rob::hal_error::success,
        nes::rob::hal_error::success,
        nes::rob::hal_error::success
    );
    fakeit::Fake(Method(mock_hal,digitalWrite));
    fakeit::Fake(Method(mock_hal,pinMode));
    WWaveDriver w_wave_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    w_wave_driver.pulse(!0);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,pinMode) + Method(mock_hal,digitalWrite) + Method(mock_hal,delayMicroseconds)).Once();
    fakeit::VerifyNoOtherInvocations(mock_hal);
    CHECK(true);
}

TEST_CASE("WWaveDriver::pulse() called with a non-zero value, returns `pulse_driver_error::hal_gpio_config`, when second invocation of pinMode() returns an error", "[pulse][active][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::Fake(Method(mock_hal,delayMicroseconds));
    fakeit::Fake(Method(mock_hal,digitalWrite));
    fakeit::When(Method(mock_hal,pinMode)).Return(
        nes::rob::hal_error::success,
        nes::rob::hal_error::peripheral_gpio,
        nes::rob::hal_error::success,
        nes::rob::hal_error::success
    );
    WWaveDriver w_wave_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const std::error_code result = w_wave_driver.pulse(!0);

    // Evalulate Result
    CHECK(nes::rob::pulse_driver_error::hal_gpio_config == result);
}

TEST_CASE("WWaveDriver::pulse() called with a non-zero value, will stop processing if the second invocation of pinMode() returns an error", "[pulse][active][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::Fake(Method(mock_hal,delayMicroseconds));
    fakeit::Fake(Method(mock_hal,digitalWrite));
    fakeit::When(Method(mock_hal,pinMode)).Return(
        nes::rob::hal_error::success,
        nes::rob::hal_error::peripheral_gpio,
        nes::rob::hal_error::success,
        nes::rob::hal_error::success
    );
    WWaveDriver w_wave_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    w_wave_driver.pulse(!0);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,pinMode) + Method(mock_hal,digitalWrite) + Method(mock_hal,delayMicroseconds) + Method(mock_hal,pinMode)).Once();
    fakeit::VerifyNoOtherInvocations(mock_hal);
    CHECK(true);
}

TEST_CASE("WWaveDriver::pulse() called with a non-zero value, returns `pulse_driver_error::hal_clock`, when second invocation of delayMicroseconds() returns an error", "[pulse][active][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).Return(
        nes::rob::hal_error::success,
        nes::rob::hal_error::sys_clock,
        nes::rob::hal_error::success,
        nes::rob::hal_error::success
    );
    fakeit::Fake(Method(mock_hal,digitalWrite));
    fakeit::Fake(Method(mock_hal,pinMode));
    WWaveDriver w_wave_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const std::error_code result = w_wave_driver.pulse(!0);

    // Evalulate Result
    CHECK(nes::rob::pulse_driver_error::hal_clock == result);
}

TEST_CASE("WWaveDriver::pulse() called with a non-zero value, will stop processing if the second invocation of delayMicroseconds() returns an error", "[pulse][active][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).Return(
        nes::rob::hal_error::success,
        nes::rob::hal_error::sys_clock,
        nes::rob::hal_error::success,
        nes::rob::hal_error::success
    );
    fakeit::Fake(Method(mock_hal,digitalWrite));
    fakeit::Fake(Method(mock_hal,pinMode));
    WWaveDriver w_wave_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    w_wave_driver.pulse(!0);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,pinMode) + Method(mock_hal,digitalWrite) + Method(mock_hal,delayMicroseconds) + Method(mock_hal,pinMode) + Method(mock_hal,delayMicroseconds)).Once();
    fakeit::VerifyNoOtherInvocations(mock_hal);
    CHECK(true);
}

TEST_CASE("WWaveDriver::pulse() called with a non-zero value, returns `pulse_driver_error::hal_gpio_config`, when third invocation of pinMode() returns an error", "[pulse][active][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::Fake(Method(mock_hal,delayMicroseconds));
    fakeit::Fake(Method(mock_hal,digitalWrite));
    fakeit::When(Method(mock_hal,pinMode)).Return(
        nes::rob::hal_error::success,
        nes::rob::hal_error::success,
        nes::rob::hal_error::peripheral_gpio,
        nes::rob::hal_error::success
    );
    WWaveDriver w_wave_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const std::error_code result = w_wave_driver.pulse(!0);

    // Evalulate Result
    CHECK(nes::rob::pulse_driver_error::hal_gpio_config == result);
}

TEST_CASE("WWaveDriver::pulse() called with a non-zero value, will stop processing if the third invocation of pinMode() returns an error", "[pulse][active][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::Fake(Method(mock_hal,delayMicroseconds));
    fakeit::Fake(Method(mock_hal,digitalWrite));
    fakeit::When(Method(mock_hal,pinMode)).Return(
        nes::rob::hal_error::success,
        nes::rob::hal_error::success,
        nes::rob::hal_error::peripheral_gpio,
        nes::rob::hal_error::success
    );
    WWaveDriver w_wave_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    w_wave_driver.pulse(!0);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,pinMode) + Method(mock_hal,digitalWrite) + Method(mock_hal,delayMicroseconds) + Method(mock_hal,pinMode) + Method(mock_hal,delayMicroseconds) + Method(mock_hal,pinMode)).Once();
    fakeit::VerifyNoOtherInvocations(mock_hal);
    CHECK(true);
}

TEST_CASE("WWaveDriver::pulse() called with a non-zero value, returns `pulse_driver_error::hal_gpio_state`, when second invocation of digitalWrite() returns an error", "[pulse][active][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::Fake(Method(mock_hal,delayMicroseconds));
    fakeit::When(Method(mock_hal,digitalWrite)).Return(
        nes::rob::hal_error::success,
        nes::rob::hal_error::peripheral_gpio
    );
    fakeit::Fake(Method(mock_hal,pinMode));
    WWaveDriver w_wave_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const std::error_code result = w_wave_driver.pulse(!0);

    // Evalulate Result
    CHECK(nes::rob::pulse_driver_error::hal_gpio_state == result);
}

TEST_CASE("WWaveDriver::pulse() called with a non-zero value, will stop processing if the second invocation of digitalWrite() returns an error", "[pulse][active][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::Fake(Method(mock_hal,delayMicroseconds));
    fakeit::When(Method(mock_hal,digitalWrite)).Return(
        nes::rob::hal_error::success,
        nes::rob::hal_error::peripheral_gpio
    );
    fakeit::Fake(Method(mock_hal,pinMode));
    WWaveDriver w_wave_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    w_wave_driver.pulse(!0);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,pinMode) + Method(mock_hal,digitalWrite) + Method(mock_hal,delayMicroseconds) + Method(mock_hal,pinMode) + Method(mock_hal,delayMicroseconds) + Method(mock_hal,pinMode) + Method(mock_hal,digitalWrite)).Once();
    fakeit::VerifyNoOtherInvocations(mock_hal);
    CHECK(true);
}

TEST_CASE("WWaveDriver::pulse() called with a non-zero value, returns `pulse_driver_error::hal_clock`, when third invocation of delayMicroseconds() returns an error", "[pulse][active][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).Return(
        nes::rob::hal_error::success,
        nes::rob::hal_error::success,
        nes::rob::hal_error::sys_clock,
        nes::rob::hal_error::success
    );
    fakeit::Fake(Method(mock_hal,digitalWrite));
    fakeit::Fake(Method(mock_hal,pinMode));
    WWaveDriver w_wave_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const std::error_code result = w_wave_driver.pulse(!0);

    // Evalulate Result
    CHECK(nes::rob::pulse_driver_error::hal_clock == result);
}

TEST_CASE("WWaveDriver::pulse() called with a non-zero value, will stop processing if the third invocation of delayMicroseconds() returns an error", "[pulse][active][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).Return(
        nes::rob::hal_error::success,
        nes::rob::hal_error::success,
        nes::rob::hal_error::sys_clock,
        nes::rob::hal_error::success
    );
    fakeit::Fake(Method(mock_hal,digitalWrite));
    fakeit::Fake(Method(mock_hal,pinMode));
    WWaveDriver w_wave_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    w_wave_driver.pulse(!0);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,pinMode) + Method(mock_hal,digitalWrite) + Method(mock_hal,delayMicroseconds) + Method(mock_hal,pinMode) + Method(mock_hal,delayMicroseconds) + Method(mock_hal,pinMode) + Method(mock_hal,digitalWrite) + Method(mock_hal,delayMicroseconds)).Once();
    fakeit::VerifyNoOtherInvocations(mock_hal);
    CHECK(true);
}

TEST_CASE("WWaveDriver::pulse() called with a non-zero value, returns `pulse_driver_error::hal_gpio_config`, when fourth invocation of pinMode() returns an error", "[pulse][active][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::Fake(Method(mock_hal,delayMicroseconds));
    fakeit::Fake(Method(mock_hal,digitalWrite));
    fakeit::When(Method(mock_hal,pinMode)).Return(
        nes::rob::hal_error::success,
        nes::rob::hal_error::success,
        nes::rob::hal_error::success,
        nes::rob::hal_error::peripheral_gpio
    );
    WWaveDriver w_wave_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const std::error_code result = w_wave_driver.pulse(!0);

    // Evalulate Result
    CHECK(nes::rob::pulse_driver_error::hal_gpio_config == result);
}

TEST_CASE("WWaveDriver::pulse() called with a non-zero value, will stop processing if the fourth invocation of pinMode() returns an error", "[pulse][active][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::Fake(Method(mock_hal,delayMicroseconds));
    fakeit::Fake(Method(mock_hal,digitalWrite));
    fakeit::When(Method(mock_hal,pinMode)).Return(
        nes::rob::hal_error::success,
        nes::rob::hal_error::success,
        nes::rob::hal_error::success,
        nes::rob::hal_error::peripheral_gpio
    );
    WWaveDriver w_wave_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    w_wave_driver.pulse(!0);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,pinMode) + Method(mock_hal,digitalWrite) + Method(mock_hal,delayMicroseconds) + Method(mock_hal,pinMode) + Method(mock_hal,delayMicroseconds) + Method(mock_hal,pinMode) + Method(mock_hal,digitalWrite) + Method(mock_hal,delayMicroseconds) + Method(mock_hal,pinMode)).Once();
    fakeit::VerifyNoOtherInvocations(mock_hal);
    CHECK(true);
}

TEST_CASE("WWaveDriver::pulse() called with a non-zero value, returns `pulse_driver_error::hal_clock`, when fourth invocation of delayMicroseconds() returns an error", "[pulse][active][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).Return(
        nes::rob::hal_error::success,
        nes::rob::hal_error::success,
        nes::rob::hal_error::success,
        nes::rob::hal_error::sys_clock
    );
    fakeit::Fake(Method(mock_hal,digitalWrite));
    fakeit::Fake(Method(mock_hal,pinMode));
    WWaveDriver w_wave_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const std::error_code result = w_wave_driver.pulse(!0);

    // Evalulate Result
    CHECK(nes::rob::pulse_driver_error::hal_clock == result);
}

TEST_CASE("WWaveDriver::pulse() called with a non-zero value, returns `pulse_driver_error::success`, when no errors are encountered", "[pulse][active][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,pinMode)).AlwaysReturn(nes::rob::hal_error::success);
    WWaveDriver w_wave_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const std::error_code result = w_wave_driver.pulse(!0);

    // Evalulate Result
    CHECK(nes::rob::pulse_driver_error::success == result);
}

TEST_CASE("WWaveDriver::pulse() called with a zero value, returns `pulse_driver_error::hal_gpio_config`, when pinMode() returns an error", "[pulse][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::Fake(Method(mock_hal,delayMicroseconds));
    fakeit::When(Method(mock_hal,pinMode)).Return(nes::rob::hal_error::peripheral_gpio);
    WWaveDriver w_wave_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const std::error_code result = w_wave_driver.pulse(0);

    // Evalulate Result
    CHECK(nes::rob::pulse_driver_error::hal_gpio_config == result);
}

TEST_CASE("WWaveDriver::pulse() called with a zero value, will stop processing if digitalWrite() returns an error", "[pulse][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::Fake(Method(mock_hal,delayMicroseconds));
    fakeit::When(Method(mock_hal,pinMode)).Return(nes::rob::hal_error::peripheral_gpio);
    WWaveDriver w_wave_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    w_wave_driver.pulse(0);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,pinMode)).Once();
    fakeit::VerifyNoOtherInvocations(mock_hal);
    CHECK(true);
}

TEST_CASE("WWaveDriver::pulse() called with a zero value, returns `pulse_driver_error::hal_clock`, when delayMicroseconds() returns an error", "[pulse][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).Return(nes::rob::hal_error::sys_clock);
    fakeit::Fake(Method(mock_hal,pinMode));
    WWaveDriver w_wave_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const std::error_code result = w_wave_driver.pulse(0);

    // Evalulate Result
    CHECK(nes::rob::pulse_driver_error::hal_clock == result);
}

TEST_CASE("WWaveDriver::pulse() called with a zero value, returns `pulse_driver_error::success`, when no errors occur", "[pulse][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,pinMode)).AlwaysReturn(nes::rob::hal_error::success);
    WWaveDriver w_wave_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const std::error_code result = w_wave_driver.pulse(0);

    // Evalulate Result
    CHECK(nes::rob::pulse_driver_error::success == result);
}
