#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include <fakeit.hpp>

// Compile Command: g++ led_ntsc_driver.test.cpp ../src/led_ntsc_driver.cpp -Wall -Wpedantic -I ../src/ -I Catch2/single_include/ -I FakeIt/single_header/catch/

#include "hardware_abstraction_layer.hpp"
#include "led_ntsc_driver.hpp"

const int HardwareAbstractionLayer::PIN_STATE_HIGH = 10;
const int HardwareAbstractionLayer::PIN_MODE_INPUT = 20;
const int HardwareAbstractionLayer::PIN_MODE_INPUT_PULLUP = 30;
const int HardwareAbstractionLayer::PIN_STATE_LOW = 40;
const int HardwareAbstractionLayer::PIN_MODE_OUTPUT = 50;

TEST_CASE("HardwareAbstractionLayer::init() is invoked during init()", "[init][hal]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::Fake(Method(mock_hal,digitalWrite));
    fakeit::When(Method(mock_hal,init)).AlwaysReturn(0);
    fakeit::Fake(Method(mock_hal,pinMode));
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    led_ntsc_driver.init(nullptr);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,init)).Once();
    CHECK(true);
}

TEST_CASE("Pin provided to constructor is set to HardwareAbstractionLayer::PIN_MODE_OUTPUT during init()", "[constructor][init][hal][pin_mode]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::Fake(Method(mock_hal,digitalWrite));
    fakeit::Fake(Method(mock_hal,init));
    fakeit::When(Method(mock_hal,pinMode)).AlwaysReturn(0);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    led_ntsc_driver.init(nullptr);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,pinMode)).Once();
    fakeit::Verify(Method(mock_hal,pinMode).Using(TEST_PIN, HardwareAbstractionLayer::PIN_MODE_OUTPUT));
    CHECK(true);
}

TEST_CASE("Pin provided to constructor is set to HardwareAbstractionLayer::PIN_STATE_LOW during init()", "[constructor][init][hal][pin_state]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(0);
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

TEST_CASE("init() returns `E_HAL_INIT`, when HardwareAbstractionLayer::init() returns an error", "[init][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(0);
    fakeit::When(Method(mock_hal,init)).AlwaysReturn(1);
    fakeit::When(Method(mock_hal,pinMode)).AlwaysReturn(0);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const int result = led_ntsc_driver.init(nullptr);

    // Evalulate Result
    CHECK(PulseDriver::ErrorCode::E_HAL_INIT == static_cast<PulseDriver::ErrorCode>(result));
}

TEST_CASE("init() will stop processing if HardwareAbstractionLayer::init() returns an error", "[init][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(0);
    fakeit::When(Method(mock_hal,init)).AlwaysReturn(1);
    fakeit::When(Method(mock_hal,pinMode)).AlwaysReturn(0);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    led_ntsc_driver.init(nullptr);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,init)).Once();
    fakeit::VerifyNoOtherInvocations(mock_hal);
    CHECK(true);
}

TEST_CASE("init() returns `E_HAL_GPIO_CFG`, when pinMode() returns an error", "[init][hal][pin_mode][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(0);
    fakeit::When(Method(mock_hal,init)).AlwaysReturn(0);
    fakeit::When(Method(mock_hal,pinMode)).AlwaysReturn(1);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const int result = led_ntsc_driver.init(nullptr);

    // Evalulate Result
    CHECK(PulseDriver::ErrorCode::E_HAL_GPIO_CFG == static_cast<PulseDriver::ErrorCode>(result));
}

TEST_CASE("init() will stop processing if pinMode() returns an error", "[init][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(0);
    fakeit::When(Method(mock_hal,init)).AlwaysReturn(0);
    fakeit::When(Method(mock_hal,pinMode)).AlwaysReturn(1);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    led_ntsc_driver.init(nullptr);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,init) + Method(mock_hal,pinMode)).Once();
    fakeit::VerifyNoOtherInvocations(mock_hal);
    CHECK(true);
}

TEST_CASE("init() returns `E_HAL_GPIO`, when digitalWrite() returns an error", "[init][hal][pin_state][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(1);
    fakeit::When(Method(mock_hal,init)).AlwaysReturn(0);
    fakeit::When(Method(mock_hal,pinMode)).AlwaysReturn(0);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const int result = led_ntsc_driver.init(nullptr);

    // Evalulate Result
    CHECK(PulseDriver::ErrorCode::E_HAL_GPIO == static_cast<PulseDriver::ErrorCode>(result));
}

TEST_CASE("init() will stop processing if digitalWrite() returns an error", "[init][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(1);
    fakeit::When(Method(mock_hal,init)).AlwaysReturn(0);
    fakeit::When(Method(mock_hal,pinMode)).AlwaysReturn(0);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    led_ntsc_driver.init(nullptr);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,init) + Method(mock_hal,pinMode) + Method(mock_hal,digitalWrite)).Once();
    fakeit::VerifyNoOtherInvocations(mock_hal);
    CHECK(true);
}

TEST_CASE("init() returns `SUCCESS`, when no errors occur", "[init][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(0);
    fakeit::When(Method(mock_hal,init)).AlwaysReturn(0);
    fakeit::When(Method(mock_hal,pinMode)).AlwaysReturn(0);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const int result = led_ntsc_driver.init(nullptr);

    // Evalulate Result
    CHECK(PulseDriver::ErrorCode::SUCCESS == static_cast<PulseDriver::ErrorCode>(result));
}

TEST_CASE("Pin provided to constructor is supplied to HAL interface when pulse() is called with a non-zero value", "[constructor][pulse][hal]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).AlwaysReturn(0);
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(0);
    fakeit::When(Method(mock_hal,pinMode)).AlwaysReturn(0);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    led_ntsc_driver.pulse(!0);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,digitalWrite).Using(TEST_PIN, fakeit::_)).Exactly(2);
    CHECK(true);
}

TEST_CASE("Pin provided to constructor is supplied to HAL interface when pulse() is called with a zero value", "[constructor][pulse][hal]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).AlwaysReturn(0);
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(0);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    led_ntsc_driver.pulse(0);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,digitalWrite).Using(TEST_PIN, fakeit::_)).Once();
    CHECK(true);
}

TEST_CASE("pulse() generates NTSC compatible pulse when called with a non-zero value", "[pulse][hal][pin_state]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).AlwaysReturn(0);
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(0);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    led_ntsc_driver.pulse(!0);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,digitalWrite) + Method(mock_hal,delayMicroseconds) + Method(mock_hal,digitalWrite) + Method(mock_hal,delayMicroseconds)).Once();
    fakeit::Verify(Method(mock_hal,digitalWrite).Using(fakeit::_, HardwareAbstractionLayer::PIN_STATE_HIGH) + Method(mock_hal,delayMicroseconds).Using(1500) + Method(mock_hal,digitalWrite).Using(fakeit::_, HardwareAbstractionLayer::PIN_STATE_LOW) + Method(mock_hal,delayMicroseconds).Using(15166));
    CHECK(true);
}

TEST_CASE("pulse() generates NTSC compatible blank called with a zero value", "[pulse][hal][pin_state]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).AlwaysReturn(0);
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(0);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    led_ntsc_driver.pulse(0);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,digitalWrite) + Method(mock_hal,delayMicroseconds)).Once();
    fakeit::Verify(Method(mock_hal,digitalWrite).Using(fakeit::_, HardwareAbstractionLayer::PIN_STATE_LOW) + Method(mock_hal,delayMicroseconds).Using(16666));
    CHECK(true);
}

TEST_CASE("pulse() called with a non-zero value, returns `E_HAL_GPIO`, when first invocation of digitalWrite() returns an error", "[pulse][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).AlwaysReturn(0);
    fakeit::When(Method(mock_hal,digitalWrite)).Return(1,0);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const int result = led_ntsc_driver.pulse(!0);

    // Evalulate Result
    CHECK(PulseDriver::ErrorCode::E_HAL_GPIO == static_cast<PulseDriver::ErrorCode>(result));
}

TEST_CASE("pulse() called with a non-zero value, will stop processing if the first invocation of digitalWrite() returns an error", "[pulse][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).AlwaysReturn(0);
    fakeit::When(Method(mock_hal,digitalWrite)).Return(1,0);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    led_ntsc_driver.pulse(!0);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,digitalWrite)).Once();
    fakeit::VerifyNoOtherInvocations(mock_hal);
    CHECK(true);
}

TEST_CASE("pulse() called with a non-zero value, returns `E_HAL_GPIO`, when second invocation of digitalWrite() returns an error", "[pulse][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).AlwaysReturn(0);
    fakeit::When(Method(mock_hal,digitalWrite)).Return(0,1);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const int result = led_ntsc_driver.pulse(!0);

    // Evalulate Result
    CHECK(PulseDriver::ErrorCode::E_HAL_GPIO == static_cast<PulseDriver::ErrorCode>(result));
}

TEST_CASE("pulse() called with a non-zero value, will stop processing if the second invocation of digitalWrite() returns an error", "[pulse][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).AlwaysReturn(0);
    fakeit::When(Method(mock_hal,digitalWrite)).Return(0,1);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    led_ntsc_driver.pulse(!0);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,digitalWrite) + Method(mock_hal,delayMicroseconds) + Method(mock_hal,digitalWrite)).Once();
    fakeit::VerifyNoOtherInvocations(mock_hal);
    CHECK(true);
}

TEST_CASE("pulse() called with a zero value, returns `E_HAL_GPIO`, when digitalWrite() returns an error", "[pulse][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).AlwaysReturn(0);
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(1);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const int result = led_ntsc_driver.pulse(0);

    // Evalulate Result
    CHECK(PulseDriver::ErrorCode::E_HAL_GPIO == static_cast<PulseDriver::ErrorCode>(result));
}

TEST_CASE("pulse() called with a zero value, will stop processing if digitalWrite() returns an error", "[pulse][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).AlwaysReturn(0);
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(1);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    led_ntsc_driver.pulse(0);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,digitalWrite)).Once();
    fakeit::VerifyNoOtherInvocations(mock_hal);
    CHECK(true);
}

TEST_CASE("pulse() called with a non-zero value, returns `E_HAL_CLOCK`, when first invocation of delayMicroseconds() returns an error", "[pulse][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).Return(1,0);
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(0);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const int result = led_ntsc_driver.pulse(!0);

    // Evalulate Result
    CHECK(PulseDriver::ErrorCode::E_HAL_CLOCK == static_cast<PulseDriver::ErrorCode>(result));
}

TEST_CASE("pulse() called with a non-zero value, will stop processing if the first invocation of delayMicroseconds() returns an error", "[pulse][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).Return(1,0);
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(0);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    led_ntsc_driver.pulse(!0);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,digitalWrite) + Method(mock_hal,delayMicroseconds)).Once();
    fakeit::VerifyNoOtherInvocations(mock_hal);
    CHECK(true);
}

TEST_CASE("pulse() called with a non-zero value, returns `E_HAL_CLOCK`, when second invocation of delayMicroseconds() returns an error", "[pulse][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).Return(0,1);
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(0);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const int result = led_ntsc_driver.pulse(!0);

    // Evalulate Result
    CHECK(PulseDriver::ErrorCode::E_HAL_CLOCK == static_cast<PulseDriver::ErrorCode>(result));
}

TEST_CASE("pulse() called with a non-zero value, will stop processing if the second invocation of delayMicroseconds() returns an error", "[pulse][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).Return(0,1);
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(0);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    led_ntsc_driver.pulse(!0);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,digitalWrite) + Method(mock_hal,delayMicroseconds) + Method(mock_hal,digitalWrite) + Method(mock_hal,delayMicroseconds)).Once();
    fakeit::VerifyNoOtherInvocations(mock_hal);
    CHECK(true);
}

TEST_CASE("pulse() called with a zero value, returns `E_HAL_CLOCK`, when delayMicroseconds() returns an error", "[pulse][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).AlwaysReturn(1);
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(0);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const int result = led_ntsc_driver.pulse(0);

    // Evalulate Result
    CHECK(PulseDriver::ErrorCode::E_HAL_CLOCK == static_cast<PulseDriver::ErrorCode>(result));
}

TEST_CASE("pulse() called with a zero value, will stop processing if delayMicroseconds() returns an error", "[pulse][hal][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).AlwaysReturn(1);
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(0);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    led_ntsc_driver.pulse(0);

    // Evalulate Result
    fakeit::Verify(Method(mock_hal,digitalWrite) + Method(mock_hal,delayMicroseconds)).Once();
    fakeit::VerifyNoOtherInvocations(mock_hal);
    CHECK(true);
}

TEST_CASE("pulse() called with a non-zero value, returns `SUCCESS`, when no errors occur", "[pulse][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).AlwaysReturn(0);
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(0);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const int result = led_ntsc_driver.pulse(!0);

    // Evalulate Result
    CHECK(PulseDriver::ErrorCode::SUCCESS == static_cast<PulseDriver::ErrorCode>(result));
}

TEST_CASE("pulse() called with a zero value, returns `SUCCESS`, when no errors occur", "[pulse][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HardwareAbstractionLayer> mock_hal;
    fakeit::When(Method(mock_hal,delayMicroseconds)).AlwaysReturn(0);
    fakeit::When(Method(mock_hal,digitalWrite)).AlwaysReturn(0);
    LedNtscDriver led_ntsc_driver(&mock_hal.get(),TEST_PIN);
    mock_hal.ClearInvocationHistory();

    // Action
    const int result = led_ntsc_driver.pulse(0);

    // Evalulate Result
    CHECK(PulseDriver::ErrorCode::SUCCESS == static_cast<PulseDriver::ErrorCode>(result));
}
