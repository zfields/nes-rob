#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include <fakeit.hpp>

// Compile Command: g++ led_ntsc_driver.test.cpp ../src/led_ntsc_driver.cpp -I../src/ -I Catch2/single_include/ -I FakeIt/single_header/catch/

#include "hal_clock.hpp"
#include "hal_gpio.hpp"
#include "led_ntsc_driver.hpp"

const int HalGpio::PIN_STATE_HIGH = 10;
const int HalGpio::PIN_MODE_INPUT = 20;
const int HalGpio::PIN_MODE_INPUT_PULLUP = 30;
const int HalGpio::PIN_STATE_LOW = 40;
const int HalGpio::PIN_MODE_OUTPUT = 50;

TEST_CASE("Pin provided to constructor is set to HalGpio::PIN_MODE_OUTPUT during init()", "[constructor][init][hal_gpio][pin_mode]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HalClock> mock_clock;
    fakeit::Mock<HalGpio> mock_gpio;
    fakeit::When(Method(mock_gpio,digitalWrite)).AlwaysReturn(0);
    fakeit::When(Method(mock_gpio,pinMode)).AlwaysReturn(0);
    LedNtscDriver led_ntsc_driver(&mock_clock.get(),&mock_gpio.get(),TEST_PIN);
    mock_gpio.ClearInvocationHistory();

    // Action
    led_ntsc_driver.init(nullptr);

    // Evalulate Result
    fakeit::Verify(Method(mock_gpio,pinMode)).Once();
    fakeit::Verify(Method(mock_gpio,pinMode).Using(TEST_PIN, HalGpio::PIN_MODE_OUTPUT));
    CHECK(true);
}

TEST_CASE("Pin provided to constructor is set to HalGpio::PIN_STATE_LOW during init()", "[constructor][init][hal_gpio][pin_state]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HalClock> mock_clock;
    fakeit::Mock<HalGpio> mock_gpio;
    fakeit::When(Method(mock_gpio,digitalWrite)).AlwaysReturn(0);
    fakeit::When(Method(mock_gpio,pinMode)).AlwaysReturn(0);
    LedNtscDriver led_ntsc_driver(&mock_clock.get(),&mock_gpio.get(),TEST_PIN);
    mock_gpio.ClearInvocationHistory();

    // Action
    led_ntsc_driver.init(nullptr);

    // Evalulate Result
    fakeit::Verify(Method(mock_gpio,digitalWrite)).Once();
    fakeit::Verify(Method(mock_gpio,digitalWrite).Using(TEST_PIN, HalGpio::PIN_STATE_LOW));
    CHECK(true);
}

TEST_CASE("init() returns `E_HAL_FAIL`, when pinMode() returns an error", "[init][hal_gpio][pin_mode][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HalClock> mock_clock;
    fakeit::Mock<HalGpio> mock_gpio;
    fakeit::When(Method(mock_gpio,digitalWrite)).AlwaysReturn(0);
    fakeit::When(Method(mock_gpio,pinMode)).AlwaysReturn(1);
    LedNtscDriver led_ntsc_driver(&mock_clock.get(),&mock_gpio.get(),TEST_PIN);
    mock_gpio.ClearInvocationHistory();

    // Action
    const PulseDriver::ErrorCode result = led_ntsc_driver.init(nullptr);

    // Evalulate Result
    CHECK(PulseDriver::ErrorCode::E_HAL_FAIL == result);
}

TEST_CASE("init() returns `E_HAL_FAIL`, when digitalWrite() returns an error", "[init][hal_gpio][pin_state][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HalClock> mock_clock;
    fakeit::Mock<HalGpio> mock_gpio;
    fakeit::When(Method(mock_gpio,digitalWrite)).AlwaysReturn(1);
    fakeit::When(Method(mock_gpio,pinMode)).AlwaysReturn(0);
    LedNtscDriver led_ntsc_driver(&mock_clock.get(),&mock_gpio.get(),TEST_PIN);
    mock_gpio.ClearInvocationHistory();

    // Action
    const PulseDriver::ErrorCode result = led_ntsc_driver.init(nullptr);

    // Evalulate Result
    CHECK(PulseDriver::ErrorCode::E_HAL_FAIL == result);
}

TEST_CASE("init() will stop processing if pinMode() returns an error", "[init][hal_gpio][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HalClock> mock_clock;
    fakeit::Mock<HalGpio> mock_gpio;
    fakeit::When(Method(mock_gpio,digitalWrite)).AlwaysReturn(0);
    fakeit::When(Method(mock_gpio,pinMode)).AlwaysReturn(1);
    LedNtscDriver led_ntsc_driver(&mock_clock.get(),&mock_gpio.get(),TEST_PIN);
    mock_gpio.ClearInvocationHistory();

    // Action
    led_ntsc_driver.init(nullptr);

    // Evalulate Result
    fakeit::Verify(Method(mock_gpio,pinMode)).Once();
    fakeit::Verify(Method(mock_gpio,digitalWrite)).Never();
    CHECK(true);
}

TEST_CASE("init() returns `SUCCESS`, when no errors occur", "[init][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HalClock> mock_clock;
    fakeit::Mock<HalGpio> mock_gpio;
    fakeit::When(Method(mock_gpio,digitalWrite)).AlwaysReturn(0);
    fakeit::When(Method(mock_gpio,pinMode)).AlwaysReturn(0);
    LedNtscDriver led_ntsc_driver(&mock_clock.get(),&mock_gpio.get(),TEST_PIN);
    mock_gpio.ClearInvocationHistory();

    // Action
    const PulseDriver::ErrorCode result = led_ntsc_driver.init(nullptr);

    // Evalulate Result
    CHECK(PulseDriver::ErrorCode::SUCCESS == result);
}

TEST_CASE("Pin provided to constructor is supplied to HAL interface when pulse() is called with a non-zero value", "[constructor][pulse][hal_gpio]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HalClock> mock_clock;
    fakeit::When(Method(mock_clock,delayMicroseconds)).AlwaysReturn(0);
    fakeit::Mock<HalGpio> mock_gpio;
    fakeit::When(Method(mock_gpio,digitalWrite)).AlwaysReturn(0);
    fakeit::When(Method(mock_gpio,pinMode)).AlwaysReturn(0);
    LedNtscDriver led_ntsc_driver(&mock_clock.get(),&mock_gpio.get(),TEST_PIN);
    mock_gpio.ClearInvocationHistory();

    // Action
    led_ntsc_driver.pulse(!0);

    // Evalulate Result
    fakeit::Verify(Method(mock_gpio,digitalWrite).Using(TEST_PIN, fakeit::_)).Exactly(2);
    CHECK(true);
}

TEST_CASE("Pin provided to constructor is supplied to HAL interface when pulse() is called with a zero value", "[constructor][pulse][hal_gpio]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HalClock> mock_clock;
    fakeit::When(Method(mock_clock,delayMicroseconds)).AlwaysReturn(0);
    fakeit::Mock<HalGpio> mock_gpio;
    fakeit::When(Method(mock_gpio,digitalWrite)).AlwaysReturn(0);
    LedNtscDriver led_ntsc_driver(&mock_clock.get(),&mock_gpio.get(),TEST_PIN);
    mock_gpio.ClearInvocationHistory();

    // Action
    led_ntsc_driver.pulse(0);

    // Evalulate Result
    fakeit::Verify(Method(mock_gpio,digitalWrite).Using(TEST_PIN, fakeit::_)).Once();
    CHECK(true);
}

TEST_CASE("pulse() generates NTSC compatible pulse when called with a non-zero value", "[pulse][hal_clock][hal_gpio][pin_state]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HalClock> mock_clock;
    fakeit::When(Method(mock_clock,delayMicroseconds)).AlwaysReturn(0);
    fakeit::Mock<HalGpio> mock_gpio;
    fakeit::When(Method(mock_gpio,digitalWrite)).AlwaysReturn(0);
    LedNtscDriver led_ntsc_driver(&mock_clock.get(),&mock_gpio.get(),TEST_PIN);
    mock_gpio.ClearInvocationHistory();

    // Action
    led_ntsc_driver.pulse(!0);

    // Evalulate Result
    fakeit::Verify(Method(mock_gpio,digitalWrite) + Method(mock_clock,delayMicroseconds) + Method(mock_gpio,digitalWrite) + Method(mock_clock,delayMicroseconds)).Once();
    fakeit::Verify(Method(mock_gpio,digitalWrite).Using(fakeit::_, HalGpio::PIN_STATE_HIGH) + Method(mock_clock,delayMicroseconds).Using(1500) + Method(mock_gpio,digitalWrite).Using(fakeit::_, HalGpio::PIN_STATE_LOW) + Method(mock_clock,delayMicroseconds).Using(15166));
    CHECK(true);
}

TEST_CASE("pulse() generates NTSC compatible blank called with a zero value", "[pulse][hal_clock][hal_gpio][pin_state]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HalClock> mock_clock;
    fakeit::When(Method(mock_clock,delayMicroseconds)).AlwaysReturn(0);
    fakeit::Mock<HalGpio> mock_gpio;
    fakeit::When(Method(mock_gpio,digitalWrite)).AlwaysReturn(0);
    LedNtscDriver led_ntsc_driver(&mock_clock.get(),&mock_gpio.get(),TEST_PIN);
    mock_gpio.ClearInvocationHistory();

    // Action
    led_ntsc_driver.pulse(0);

    // Evalulate Result
    fakeit::Verify(Method(mock_gpio,digitalWrite) + Method(mock_clock,delayMicroseconds)).Once();
    fakeit::Verify(Method(mock_gpio,digitalWrite).Using(fakeit::_, HalGpio::PIN_STATE_LOW) + Method(mock_clock,delayMicroseconds).Using(16666));
    CHECK(true);
}

TEST_CASE("pulse() called with a non-zero value, returns `E_HAL_FAIL`, when first invocation of digitalWrite() returns an error", "[pulse][hal_gpio][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HalClock> mock_clock;
    fakeit::When(Method(mock_clock,delayMicroseconds)).AlwaysReturn(0);
    fakeit::Mock<HalGpio> mock_gpio;
    fakeit::When(Method(mock_gpio,digitalWrite)).Return(1,0);
    LedNtscDriver led_ntsc_driver(&mock_clock.get(),&mock_gpio.get(),TEST_PIN);
    mock_gpio.ClearInvocationHistory();

    // Action
    const PulseDriver::ErrorCode result = led_ntsc_driver.pulse(!0);

    // Evalulate Result
    CHECK(PulseDriver::ErrorCode::E_HAL_FAIL == result);
}

TEST_CASE("pulse() called with a non-zero value, will stop processing if the first invocation of digitalWrite() returns an error", "[pulse][hal_gpio][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HalClock> mock_clock;
    fakeit::When(Method(mock_clock,delayMicroseconds)).AlwaysReturn(0);
    fakeit::Mock<HalGpio> mock_gpio;
    fakeit::When(Method(mock_gpio,digitalWrite)).Return(1,0);
    LedNtscDriver led_ntsc_driver(&mock_clock.get(),&mock_gpio.get(),TEST_PIN);
    mock_gpio.ClearInvocationHistory();

    // Action
    led_ntsc_driver.pulse(!0);

    // Evalulate Result
    fakeit::Verify(Method(mock_gpio,digitalWrite)).Once();
    fakeit::VerifyNoOtherInvocations(mock_clock);
    fakeit::VerifyNoOtherInvocations(mock_gpio);
    CHECK(true);
}

TEST_CASE("pulse() called with a non-zero value, returns `E_HAL_FAIL`, when second invocation of digitalWrite() returns an error", "[pulse][hal_gpio][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HalClock> mock_clock;
    fakeit::When(Method(mock_clock,delayMicroseconds)).AlwaysReturn(0);
    fakeit::Mock<HalGpio> mock_gpio;
    fakeit::When(Method(mock_gpio,digitalWrite)).Return(0,1);
    LedNtscDriver led_ntsc_driver(&mock_clock.get(),&mock_gpio.get(),TEST_PIN);
    mock_gpio.ClearInvocationHistory();

    // Action
    const PulseDriver::ErrorCode result = led_ntsc_driver.pulse(!0);

    // Evalulate Result
    CHECK(PulseDriver::ErrorCode::E_HAL_FAIL == result);
}

TEST_CASE("pulse() called with a non-zero value, will stop processing if the second invocation of digitalWrite() returns an error", "[pulse][hal_gpio][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HalClock> mock_clock;
    fakeit::When(Method(mock_clock,delayMicroseconds)).AlwaysReturn(0);
    fakeit::Mock<HalGpio> mock_gpio;
    fakeit::When(Method(mock_gpio,digitalWrite)).Return(0,1);
    LedNtscDriver led_ntsc_driver(&mock_clock.get(),&mock_gpio.get(),TEST_PIN);
    mock_gpio.ClearInvocationHistory();

    // Action
    led_ntsc_driver.pulse(!0);

    // Evalulate Result
    fakeit::Verify(Method(mock_gpio,digitalWrite) + Method(mock_clock,delayMicroseconds) + Method(mock_gpio,digitalWrite)).Once();
    fakeit::VerifyNoOtherInvocations(mock_clock);
    fakeit::VerifyNoOtherInvocations(mock_gpio);
    CHECK(true);
}

TEST_CASE("pulse() called with a zero value, returns `E_HAL_FAIL`, when digitalWrite() returns an error", "[pulse][hal_gpio][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HalClock> mock_clock;
    fakeit::When(Method(mock_clock,delayMicroseconds)).AlwaysReturn(0);
    fakeit::Mock<HalGpio> mock_gpio;
    fakeit::When(Method(mock_gpio,digitalWrite)).AlwaysReturn(1);
    LedNtscDriver led_ntsc_driver(&mock_clock.get(),&mock_gpio.get(),TEST_PIN);
    mock_gpio.ClearInvocationHistory();

    // Action
    const PulseDriver::ErrorCode result = led_ntsc_driver.pulse(0);

    // Evalulate Result
    CHECK(PulseDriver::ErrorCode::E_HAL_FAIL == result);
}

TEST_CASE("pulse() called with a zero value, will stop processing if digitalWrite() returns an error", "[pulse][hal_gpio][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HalClock> mock_clock;
    fakeit::When(Method(mock_clock,delayMicroseconds)).AlwaysReturn(0);
    fakeit::Mock<HalGpio> mock_gpio;
    fakeit::When(Method(mock_gpio,digitalWrite)).AlwaysReturn(1);
    LedNtscDriver led_ntsc_driver(&mock_clock.get(),&mock_gpio.get(),TEST_PIN);
    mock_gpio.ClearInvocationHistory();

    // Action
    led_ntsc_driver.pulse(0);

    // Evalulate Result
    fakeit::Verify(Method(mock_gpio,digitalWrite)).Once();
    fakeit::VerifyNoOtherInvocations(mock_clock);
    fakeit::VerifyNoOtherInvocations(mock_gpio);
    CHECK(true);
}

TEST_CASE("pulse() called with a non-zero value, returns `E_HAL_FAIL`, when first invocation of delayMicroseconds() returns an error", "[pulse][hal_clock][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HalClock> mock_clock;
    fakeit::When(Method(mock_clock,delayMicroseconds)).Return(1,0);
    fakeit::Mock<HalGpio> mock_gpio;
    fakeit::When(Method(mock_gpio,digitalWrite)).AlwaysReturn(0);
    LedNtscDriver led_ntsc_driver(&mock_clock.get(),&mock_gpio.get(),TEST_PIN);
    mock_gpio.ClearInvocationHistory();

    // Action
    const PulseDriver::ErrorCode result = led_ntsc_driver.pulse(!0);

    // Evalulate Result
    CHECK(PulseDriver::ErrorCode::E_HAL_FAIL == result);
}

TEST_CASE("pulse() called with a non-zero value, will stop processing if the first invocation of delayMicroseconds() returns an error", "[pulse][hal_clock][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HalClock> mock_clock;
    fakeit::When(Method(mock_clock,delayMicroseconds)).Return(1,0);
    fakeit::Mock<HalGpio> mock_gpio;
    fakeit::When(Method(mock_gpio,digitalWrite)).AlwaysReturn(0);
    LedNtscDriver led_ntsc_driver(&mock_clock.get(),&mock_gpio.get(),TEST_PIN);
    mock_gpio.ClearInvocationHistory();

    // Action
    led_ntsc_driver.pulse(!0);

    // Evalulate Result
    fakeit::Verify(Method(mock_gpio,digitalWrite) + Method(mock_clock,delayMicroseconds)).Once();
    fakeit::VerifyNoOtherInvocations(mock_clock);
    fakeit::VerifyNoOtherInvocations(mock_gpio);
    CHECK(true);
}

TEST_CASE("pulse() called with a non-zero value, returns `E_HAL_FAIL`, when second invocation of delayMicroseconds() returns an error", "[pulse][hal_clock][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HalClock> mock_clock;
    fakeit::When(Method(mock_clock,delayMicroseconds)).Return(0,1);
    fakeit::Mock<HalGpio> mock_gpio;
    fakeit::When(Method(mock_gpio,digitalWrite)).AlwaysReturn(0);
    LedNtscDriver led_ntsc_driver(&mock_clock.get(),&mock_gpio.get(),TEST_PIN);
    mock_gpio.ClearInvocationHistory();

    // Action
    const PulseDriver::ErrorCode result = led_ntsc_driver.pulse(!0);

    // Evalulate Result
    CHECK(PulseDriver::ErrorCode::E_HAL_FAIL == result);
}

TEST_CASE("pulse() called with a non-zero value, will stop processing if the second invocation of delayMicroseconds() returns an error", "[pulse][hal_clock][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HalClock> mock_clock;
    fakeit::When(Method(mock_clock,delayMicroseconds)).Return(0,1);
    fakeit::Mock<HalGpio> mock_gpio;
    fakeit::When(Method(mock_gpio,digitalWrite)).AlwaysReturn(0);
    LedNtscDriver led_ntsc_driver(&mock_clock.get(),&mock_gpio.get(),TEST_PIN);
    mock_gpio.ClearInvocationHistory();

    // Action
    led_ntsc_driver.pulse(!0);

    // Evalulate Result
    fakeit::Verify(Method(mock_gpio,digitalWrite) + Method(mock_clock,delayMicroseconds) + Method(mock_gpio,digitalWrite) + Method(mock_clock,delayMicroseconds)).Once();
    fakeit::VerifyNoOtherInvocations(mock_clock);
    fakeit::VerifyNoOtherInvocations(mock_gpio);
    CHECK(true);
}

TEST_CASE("pulse() called with a zero value, returns `E_HAL_FAIL`, when delayMicroseconds() returns an error", "[pulse][hal_clock][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HalClock> mock_clock;
    fakeit::When(Method(mock_clock,delayMicroseconds)).AlwaysReturn(1);
    fakeit::Mock<HalGpio> mock_gpio;
    fakeit::When(Method(mock_gpio,digitalWrite)).AlwaysReturn(0);
    LedNtscDriver led_ntsc_driver(&mock_clock.get(),&mock_gpio.get(),TEST_PIN);
    mock_gpio.ClearInvocationHistory();

    // Action
    const PulseDriver::ErrorCode result = led_ntsc_driver.pulse(0);

    // Evalulate Result
    CHECK(PulseDriver::ErrorCode::E_HAL_FAIL == result);
}

TEST_CASE("pulse() called with a zero value, will stop processing if delayMicroseconds() returns an error", "[pulse][hal_clock][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HalClock> mock_clock;
    fakeit::When(Method(mock_clock,delayMicroseconds)).AlwaysReturn(1);
    fakeit::Mock<HalGpio> mock_gpio;
    fakeit::When(Method(mock_gpio,digitalWrite)).AlwaysReturn(0);
    LedNtscDriver led_ntsc_driver(&mock_clock.get(),&mock_gpio.get(),TEST_PIN);
    mock_gpio.ClearInvocationHistory();

    // Action
    led_ntsc_driver.pulse(0);

    // Evalulate Result
    fakeit::Verify(Method(mock_gpio,digitalWrite) + Method(mock_clock,delayMicroseconds)).Once();
    fakeit::VerifyNoOtherInvocations(mock_clock);
    fakeit::VerifyNoOtherInvocations(mock_gpio);
    CHECK(true);
}

TEST_CASE("pulse() called with a non-zero value, returns `SUCCESS`, when no errors occur", "[pulse][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HalClock> mock_clock;
    fakeit::When(Method(mock_clock,delayMicroseconds)).AlwaysReturn(0);
    fakeit::Mock<HalGpio> mock_gpio;
    fakeit::When(Method(mock_gpio,digitalWrite)).AlwaysReturn(0);
    LedNtscDriver led_ntsc_driver(&mock_clock.get(),&mock_gpio.get(),TEST_PIN);
    mock_gpio.ClearInvocationHistory();

    // Action
    const PulseDriver::ErrorCode result = led_ntsc_driver.pulse(!0);

    // Evalulate Result
    CHECK(PulseDriver::ErrorCode::SUCCESS == result);
}

TEST_CASE("pulse() called with a zero value, returns `SUCCESS`, when no errors occur", "[pulse][error]") {
    // Setup
    static const unsigned int TEST_PIN = 13;
    fakeit::Mock<HalClock> mock_clock;
    fakeit::When(Method(mock_clock,delayMicroseconds)).AlwaysReturn(0);
    fakeit::Mock<HalGpio> mock_gpio;
    fakeit::When(Method(mock_gpio,digitalWrite)).AlwaysReturn(0);
    LedNtscDriver led_ntsc_driver(&mock_clock.get(),&mock_gpio.get(),TEST_PIN);
    mock_gpio.ClearInvocationHistory();

    // Action
    const PulseDriver::ErrorCode result = led_ntsc_driver.pulse(0);

    // Evalulate Result
    CHECK(PulseDriver::ErrorCode::SUCCESS == result);
}
