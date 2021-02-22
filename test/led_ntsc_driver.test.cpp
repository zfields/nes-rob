#ifndef RUN_ALL_TESTS
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#endif

#include <catch2/catch.hpp>
#include <fakeit.hpp>

// Compile Command: g++ led_ntsc_driver.test.cpp ../src/led_ntsc_driver.cpp ../src/hal_error.cpp ../src/pulse_driver_error.cpp -Wall -Wpedantic -I ../src/ -I Catch2/single_include/ -I FakeIt/single_header/catch/

#include "hal_error.hpp"
#include "hardware_abstraction_layer.hpp"
#include "led_ntsc_driver.hpp"
#include "pulse_driver_error.hpp"

__attribute__((weak)) const int HardwareAbstractionLayer::PIN_STATE_HIGH = 10;
__attribute__((weak)) const int HardwareAbstractionLayer::PIN_MODE_INPUT = 20;
__attribute__((weak)) const int HardwareAbstractionLayer::PIN_MODE_INPUT_PULLUP = 30;
__attribute__((weak)) const int HardwareAbstractionLayer::PIN_STATE_LOW = 40;
__attribute__((weak)) const int HardwareAbstractionLayer::PIN_MODE_OUTPUT = 50;

TEST_CASE("HardwareAbstractionLayer::init() is invoked during LedNtscDriver::init()", "[init][hal]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::Fake(Method(mock_hal,digitalWrite));
    fakeit::When(Method(mock_hal,init)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::Fake(Method(mock_hal,pinMode));
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    led_ntsc_driver.init(nullptr);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,init)).Once();
    CHECK(true);
}

TEST_CASE("Pin provided to LedNtscDriver() is set to HardwareAbstractionLayer::PIN_MODE_OUTPUT during LedNtscDriver::init()", "[constructor][init][hal][pin_mode]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::Fake(Method(mock_hal,digitalWrite));
    fakeit::Fake(Method(mock_hal,init));
    fakeit::When(Method(mock_hal,pinMode)).AlwaysReturn(nes::rob::hal_error::success);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    led_ntsc_driver.init(nullptr);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,pinMode)).Once();
    fakeit::Verify(Method(mock_hal,pinMode).Using(TEST_PIN, HardwareAbstractionLayer::PIN_MODE_OUTPUT));
    CHECK(true);
}

TEST_CASE("Pin provided to LedNtscDriver() is set to HardwareAbstractionLayer::PIN_STATE_LOW during LedNtscDriver::init()", "[constructor][init][hal][pin_state]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::Fake(Method(mock_hal,init));
    fakeit::Fake(Method(mock_hal,pinMode));
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    led_ntsc_driver.init(nullptr);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,digitalWrite)).Once();
    fakeit::Verify(Method(mock_hal,digitalWrite).Using(TEST_PIN, HardwareAbstractionLayer::PIN_STATE_LOW));
    CHECK(true);
}

TEST_CASE("LedNtscDriver::init() returns `pulse_driver_error::hal_init`, when HardwareAbstractionLayer::init() returns an error", "[init][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,init)).AlwaysReturn(nes::rob::hal_error::sys_config);
    fakeit::When(Method(mock_hal,pinMode)).AlwaysReturn(nes::rob::hal_error::success);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const std::error_code result = led_ntsc_driver.init(nullptr);

    // Evalulate Result
    CHECK(nes::rob::pulse_driver_error::hal_init == result);
}

TEST_CASE("LedNtscDriver::init() will stop processing if HardwareAbstractionLayer::init() returns an error", "[init][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,init)).AlwaysReturn(nes::rob::hal_error::sys_config);
    fakeit::When(Method(mock_hal,pinMode)).AlwaysReturn(nes::rob::hal_error::success);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    led_ntsc_driver.init(nullptr);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,init)).Once();
    fakeit::VerifyNoOtherInvocations(mock_hal);
    CHECK(true);
}

TEST_CASE("LedNtscDriver::init() returns `pulse_driver_error::hal_gpio_config`, when pinMode() returns an error", "[init][hal][pin_mode][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,init)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,pinMode)).AlwaysReturn(nes::rob::hal_error::peripheral_gpio);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const std::error_code result = led_ntsc_driver.init(nullptr);

    // Evalulate Result
    CHECK(nes::rob::pulse_driver_error::hal_gpio_config == result);
}

TEST_CASE("LedNtscDriver::init() will stop processing if pinMode() returns an error", "[init][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,init)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,pinMode)).AlwaysReturn(nes::rob::hal_error::peripheral_gpio);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    led_ntsc_driver.init(nullptr);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,init) + Method(mock_hal,pinMode)).Once();
    fakeit::VerifyNoOtherInvocations(mock_hal);
    CHECK(true);
}

TEST_CASE("LedNtscDriver::init() returns `pulse_driver_error::hal_gpio_state`, when digitalWrite() returns an error", "[init][hal][pin_state][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(nes::rob::hal_error::peripheral_gpio);
    fakeit::When(Method(mock_hal,init)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,pinMode)).AlwaysReturn(nes::rob::hal_error::success);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const std::error_code result = led_ntsc_driver.init(nullptr);

    // Evalulate Result
    CHECK(nes::rob::pulse_driver_error::hal_gpio_state == result);
}

TEST_CASE("LedNtscDriver::init() will stop processing if digitalWrite() returns an error", "[init][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(nes::rob::hal_error::peripheral_gpio);
    fakeit::When(Method(mock_hal,init)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,pinMode)).AlwaysReturn(nes::rob::hal_error::success);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    led_ntsc_driver.init(nullptr);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,init) + Method(mock_hal,pinMode) + Method(mock_hal,digitalWrite)).Once();
    fakeit::VerifyNoOtherInvocations(mock_hal);
    CHECK(true);
}

TEST_CASE("LedNtscDriver::init() returns `pulse_driver_error::success`, when no errors occur", "[init][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,init)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,pinMode)).AlwaysReturn(nes::rob::hal_error::success);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const std::error_code result = led_ntsc_driver.init(nullptr);

    // Evalulate Result
    CHECK(nes::rob::pulse_driver_error::success == result);
}

TEST_CASE("Pin provided to LedNtscDriver() is supplied to HAL interface when LedNtscDriver::pulse() is called with a non-zero value", "[constructor][pulse][hal]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,pinMode)).AlwaysReturn(nes::rob::hal_error::success);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    led_ntsc_driver.pulse(!0);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,digitalWrite).Using(TEST_PIN, fakeit::_)).Exactly(2);
    CHECK(true);
}

TEST_CASE("Pin provided to LedNtscDriver() is supplied to HAL interface when LedNtscDriver::pulse() is called with a zero value", "[constructor][pulse][hal]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(nes::rob::hal_error::success);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    led_ntsc_driver.pulse(0);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,digitalWrite).Using(TEST_PIN, fakeit::_)).Once();
    CHECK(true);
}

TEST_CASE("LedNtscDriver::pulse() generates NTSC compatible pulse when called with a non-zero value", "[pulse][hal][pin_state]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(nes::rob::hal_error::success);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    led_ntsc_driver.pulse(!0);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,digitalWrite) + Method(mock_hal,delayMicroseconds) + Method(mock_hal,digitalWrite) + Method(mock_hal,delayMicroseconds)).Once();
    fakeit::Verify(Method(mock_hal,digitalWrite).Using(fakeit::_, HardwareAbstractionLayer::PIN_STATE_HIGH) + Method(mock_hal,delayMicroseconds).Using(1500) + Method(mock_hal,digitalWrite).Using(fakeit::_, HardwareAbstractionLayer::PIN_STATE_LOW) + Method(mock_hal,delayMicroseconds).Using(15166));
    CHECK(true);
}

TEST_CASE("LedNtscDriver::pulse() generates NTSC compatible blank called with a zero value", "[pulse][hal][pin_state]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(nes::rob::hal_error::success);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    led_ntsc_driver.pulse(0);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,digitalWrite) + Method(mock_hal,delayMicroseconds)).Once();
    fakeit::Verify(Method(mock_hal,digitalWrite).Using(fakeit::_, HardwareAbstractionLayer::PIN_STATE_LOW) + Method(mock_hal,delayMicroseconds).Using(16666));
    CHECK(true);
}

TEST_CASE("LedNtscDriver::pulse() called with a non-zero value, returns `pulse_driver_error::hal_gpio_state`, when first invocation of digitalWrite() returns an error", "[pulse][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,digitalWrite)).Return(
        nes::rob::hal_error::peripheral_gpio,
        nes::rob::hal_error::success
    );
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const std::error_code result = led_ntsc_driver.pulse(!0);

    // Evalulate Result
    CHECK(nes::rob::pulse_driver_error::hal_gpio_state == result);
}

TEST_CASE("LedNtscDriver::pulse() called with a non-zero value, will stop processing if the first invocation of digitalWrite() returns an error", "[pulse][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,digitalWrite)).Return(
        nes::rob::hal_error::peripheral_gpio,
        nes::rob::hal_error::success
    );
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    led_ntsc_driver.pulse(!0);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,digitalWrite)).Once();
    fakeit::VerifyNoOtherInvocations(mock_hal);
    CHECK(true);
}

TEST_CASE("LedNtscDriver::pulse() called with a non-zero value, returns `pulse_driver_error::hal_gpio_state`, when second invocation of digitalWrite() returns an error", "[pulse][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,digitalWrite)).Return(
        nes::rob::hal_error::success,
        nes::rob::hal_error::peripheral_gpio
    );
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const std::error_code result = led_ntsc_driver.pulse(!0);

    // Evalulate Result
    CHECK(nes::rob::pulse_driver_error::hal_gpio_state == result);
}

TEST_CASE("LedNtscDriver::pulse() called with a non-zero value, will stop processing if the second invocation of digitalWrite() returns an error", "[pulse][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,digitalWrite)).Return(
        nes::rob::hal_error::success,
        nes::rob::hal_error::peripheral_gpio
    );
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    led_ntsc_driver.pulse(!0);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,digitalWrite) + Method(mock_hal,delayMicroseconds) + Method(mock_hal,digitalWrite)).Once();
    fakeit::VerifyNoOtherInvocations(mock_hal);
    CHECK(true);
}

TEST_CASE("LedNtscDriver::pulse() called with a zero value, returns `pulse_driver_error::hal_gpio_state`, when digitalWrite() returns an error", "[pulse][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(nes::rob::hal_error::peripheral_gpio);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const std::error_code result = led_ntsc_driver.pulse(0);

    // Evalulate Result
    CHECK(nes::rob::pulse_driver_error::hal_gpio_state == result);
}

TEST_CASE("LedNtscDriver::pulse() called with a zero value, will stop processing if digitalWrite() returns an error", "[pulse][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(nes::rob::hal_error::peripheral_gpio);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    led_ntsc_driver.pulse(0);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,digitalWrite)).Once();
    fakeit::VerifyNoOtherInvocations(mock_hal);
    CHECK(true);
}

TEST_CASE("LedNtscDriver::pulse() called with a non-zero value, returns `pulse_driver_error::hal_clock`, when first invocation of delayMicroseconds() returns an error", "[pulse][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).Return(
        nes::rob::hal_error::sys_clock,
        nes::rob::hal_error::success
    );
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(nes::rob::hal_error::success);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const std::error_code result = led_ntsc_driver.pulse(!0);

    // Evalulate Result
    CHECK(nes::rob::pulse_driver_error::hal_clock == result);
}

TEST_CASE("LedNtscDriver::pulse() called with a non-zero value, will stop processing if the first invocation of delayMicroseconds() returns an error", "[pulse][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).Return(
        nes::rob::hal_error::sys_clock,
        nes::rob::hal_error::success
    );
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(nes::rob::hal_error::success);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    led_ntsc_driver.pulse(!0);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,digitalWrite) + Method(mock_hal,delayMicroseconds)).Once();
    fakeit::VerifyNoOtherInvocations(mock_hal);
    CHECK(true);
}

TEST_CASE("LedNtscDriver::pulse() called with a non-zero value, returns `pulse_driver_error::hal_clock`, when second invocation of delayMicroseconds() returns an error", "[pulse][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).Return(
        nes::rob::hal_error::success,
        nes::rob::hal_error::sys_clock
    );
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(nes::rob::hal_error::success);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const std::error_code result = led_ntsc_driver.pulse(!0);

    // Evalulate Result
    CHECK(nes::rob::pulse_driver_error::hal_clock == result);
}

TEST_CASE("LedNtscDriver::pulse() called with a non-zero value, will stop processing if the second invocation of delayMicroseconds() returns an error", "[pulse][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).Return(
        nes::rob::hal_error::success,
        nes::rob::hal_error::sys_clock
    );
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(nes::rob::hal_error::success);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    led_ntsc_driver.pulse(!0);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,digitalWrite) + Method(mock_hal,delayMicroseconds) + Method(mock_hal,digitalWrite) + Method(mock_hal,delayMicroseconds)).Once();
    fakeit::VerifyNoOtherInvocations(mock_hal);
    CHECK(true);
}

TEST_CASE("LedNtscDriver::pulse() called with a zero value, returns `pulse_driver_error::hal_clock`, when delayMicroseconds() returns an error", "[pulse][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).AlwaysReturn(nes::rob::hal_error::sys_clock);
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(nes::rob::hal_error::success);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const std::error_code result = led_ntsc_driver.pulse(0);

    // Evalulate Result
    CHECK(nes::rob::pulse_driver_error::hal_clock == result);
}

TEST_CASE("LedNtscDriver::pulse() called with a zero value, will stop processing if delayMicroseconds() returns an error", "[pulse][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).AlwaysReturn(nes::rob::hal_error::sys_clock);
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(nes::rob::hal_error::success);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    led_ntsc_driver.pulse(0);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,digitalWrite) + Method(mock_hal,delayMicroseconds)).Once();
    fakeit::VerifyNoOtherInvocations(mock_hal);
    CHECK(true);
}

TEST_CASE("LedNtscDriver::pulse() called with a non-zero value, returns `pulse_driver_error::success`, when no errors occur", "[pulse][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(nes::rob::hal_error::success);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const std::error_code result = led_ntsc_driver.pulse(!0);

    // Evalulate Result
    CHECK(nes::rob::pulse_driver_error::success == result);
}

TEST_CASE("LedNtscDriver::pulse() called with a zero value, returns `pulse_driver_error::success`, when no errors occur", "[pulse][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).AlwaysReturn(nes::rob::hal_error::success);
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(nes::rob::hal_error::success);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const std::error_code result = led_ntsc_driver.pulse(0);

    // Evalulate Result
    CHECK(nes::rob::pulse_driver_error::success == result);
}
