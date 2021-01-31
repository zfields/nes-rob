#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include <fakeit.hpp>

// Compile Command: g++ signal_generator.test.cpp ../src/signal_generator.cpp -I ../src/ -I Catch2/single_include/ -I FakeIt/single_header/catch/

#include "pulse_driver.hpp"
#include "signal_generator.hpp"

TEST_CASE("PulseDriver::init() is invoked during init()", "[pulse_driver][init]") {
    // Setup
    fakeit::Mock<PulseDriver> mock_driver;
    fakeit::When(Method(mock_driver,init)).AlwaysReturn(0);
    SignalGenerator sig_gen(&mock_driver.get());

    // Action
    sig_gen.init(nullptr);

    // Evalulate Result
    fakeit::Verify(Method(mock_driver,init)).Once();
    CHECK(true);
}

TEST_CASE("init() returns `E_DRIVER`, when PulseDriver::init() returns an error", "[init][pulse_driver][error]") {
    // Setup
    fakeit::Mock<PulseDriver> mock_driver;
    fakeit::When(Method(mock_driver,init)).AlwaysReturn(1);
    SignalGenerator sig_gen(&mock_driver.get());

    // Action
    const int result = sig_gen.init(nullptr);

    // Evalulate Result
    CHECK(SignalGenerator::ErrorCode::E_DRIVER == static_cast<SignalGenerator::ErrorCode>(result));
}

TEST_CASE("init() returns `SUCCESS`, when no errors occur", "[init][error]") {
    // Setup
    fakeit::Mock<PulseDriver> mock_driver;
    fakeit::When(Method(mock_driver,init)).AlwaysReturn(0);
    SignalGenerator sig_gen(&mock_driver.get());

    // Action
    const int result = sig_gen.init(nullptr);

    // Evalulate Result
    CHECK(SignalGenerator::ErrorCode::SUCCESS == static_cast<SignalGenerator::ErrorCode>(result));
}

TEST_CASE("Sequences are 8 bits, prefixed with a 5-bit initialization sequence", "[signal][preamble]") {
    // Setup
    fakeit::Mock<PulseDriver> mock_driver;
    fakeit::When(Method(mock_driver,pulse)).AlwaysReturn(0);
    SignalGenerator sig_gen(&mock_driver.get());

    // Action
    sig_gen.signal(0xAA);

    // Evalulate Result
    fakeit::Verify(Method(mock_driver,pulse)).Exactly(13);
    CHECK(true);
}

TEST_CASE("5-bit initialization sequence is `00010`", "[signal][preamble]") {
    // Setup
    fakeit::Mock<PulseDriver> mock_driver;
    fakeit::When(Method(mock_driver,pulse)).AlwaysReturn(0);
    SignalGenerator sig_gen(&mock_driver.get());

    // Action
    sig_gen.signal(0x17);

    // Evalulate Result
    fakeit::Verify((Method(mock_driver,pulse).Using(0) * 3) + Method(mock_driver,pulse).Using(1) + Method(mock_driver,pulse).Using(0) + (Method(mock_driver,pulse).Using(fakeit::_) * 8)).Once();
    CHECK(true);
}

TEST_CASE("Sequences matches sequence parameter", "[signal][sequence]") {
    // Setup
    fakeit::Mock<PulseDriver> mock_driver;
    fakeit::When(Method(mock_driver,pulse)).AlwaysReturn(0);
    SignalGenerator sig_gen(&mock_driver.get());

    // Action
    sig_gen.signal(0xAA);

    // Evalulate Result
    fakeit::Verify((Method(mock_driver,pulse).Using(fakeit::_) * 5) + ((Method(mock_driver,pulse).Using(1) + Method(mock_driver,pulse).Using(0)) * 4)).Once();
    CHECK(true);
}

TEST_CASE("Sequences longer than 8 bits will only use the bottom 8-bits", "[signal][sequence]") {
    // Setup
    fakeit::Mock<PulseDriver> mock_driver;
    fakeit::When(Method(mock_driver,pulse)).AlwaysReturn(0);
    SignalGenerator sig_gen(&mock_driver.get());

    // Action
    sig_gen.signal(0xCC55FFAA);

    // Evalulate Result
    fakeit::Verify((Method(mock_driver,pulse).Using(fakeit::_) * 5) + ((Method(mock_driver,pulse).Using(1) + Method(mock_driver,pulse).Using(0)) * 4)).Once();
    CHECK(true);
}

TEST_CASE("signal() halts when `pulse` returns error during preamble", "[signal][error][preamble]") {
    // Setup
    fakeit::Mock<PulseDriver> mock_driver;
    fakeit::When(Method(mock_driver,pulse)).Return(0,0,1);
    SignalGenerator sig_gen(&mock_driver.get());

    // Action
    sig_gen.signal(0xAA);

    // Evalulate Result
    fakeit::Verify(Method(mock_driver,pulse)).Exactly(3);
    fakeit::VerifyNoOtherInvocations(mock_driver);
    CHECK(true);
}

TEST_CASE("signal() halts when `pulse` returns error during sequence", "[signal][error]") {
    // Setup
    fakeit::Mock<PulseDriver> mock_driver;
    fakeit::When(Method(mock_driver,pulse)).Return(0,0,0,0,0,0,0,1);
    SignalGenerator sig_gen(&mock_driver.get());

    // Action
    sig_gen.signal(0xAA);

    // Evalulate Result
    fakeit::Verify(Method(mock_driver,pulse)).Exactly(8);
    fakeit::VerifyNoOtherInvocations(mock_driver);
    CHECK(true);
}

TEST_CASE("signal() returns `E_DRIVER`, when pulse() returns an error during preamble", "[signal][error][pulse_driver][preamble]") {
    // Setup
    fakeit::Mock<PulseDriver> mock_driver;
    fakeit::When(Method(mock_driver,pulse)).Return(0,0,1);
    SignalGenerator sig_gen(&mock_driver.get());

    // Action
    const int result = sig_gen.signal(0xAA);

    // Evalulate Result
    CHECK(SignalGenerator::ErrorCode::E_DRIVER == static_cast<SignalGenerator::ErrorCode>(result));
}

TEST_CASE("signal() returns `E_DRIVER`, when pulse() returns an error during sequence", "[signal][error][pulse_driver]") {
    // Setup
    fakeit::Mock<PulseDriver> mock_driver;
    fakeit::When(Method(mock_driver,pulse)).Return(0,0,0,0,0,0,0,1);
    SignalGenerator sig_gen(&mock_driver.get());

    // Action
    const int result = sig_gen.signal(0xAA);

    // Evalulate Result
    CHECK(SignalGenerator::ErrorCode::E_DRIVER == static_cast<SignalGenerator::ErrorCode>(result));
}

TEST_CASE("signal() returns `SUCCESS`, when no errors occur", "[signal][error]") {
    // Setup
    fakeit::Mock<PulseDriver> mock_driver;
    fakeit::When(Method(mock_driver,pulse)).AlwaysReturn(0);
    SignalGenerator sig_gen(&mock_driver.get());

    // Action
    const int result = sig_gen.signal(0xAA);

    // Evalulate Result
    CHECK(SignalGenerator::ErrorCode::SUCCESS == static_cast<SignalGenerator::ErrorCode>(result));
}

TEST_CASE("testSignal() produces a 20-bit sequence", "[test_signal]") {
    // Setup
    fakeit::Mock<PulseDriver> mock_driver;
    fakeit::When(Method(mock_driver,pulse)).AlwaysReturn(0);
    SignalGenerator sig_gen(&mock_driver.get());

    // Action
    sig_gen.testSignal();

    // Evalulate Result
    fakeit::Verify(Method(mock_driver,pulse)).Exactly(20);
    CHECK(true);
}

TEST_CASE("testSignal() sequence is `10101010101010101010`", "[test_signal]") {
    // Setup
    fakeit::Mock<PulseDriver> mock_driver;
    fakeit::When(Method(mock_driver,pulse)).AlwaysReturn(0);
    SignalGenerator sig_gen(&mock_driver.get());

    // Action
    sig_gen.testSignal();

    // Evalulate Result
    fakeit::Verify((Method(mock_driver,pulse).Using(1) + Method(mock_driver,pulse).Using(0)) * 10).Once();
    CHECK(true);
}

TEST_CASE("testSignal() halts when `pulse` returns error", "[test_signal][error][pulse_driver]") {
    // Setup
    fakeit::Mock<PulseDriver> mock_driver;
    fakeit::When(Method(mock_driver,pulse)).Return(0,0,0,0,0,0,1);
    SignalGenerator sig_gen(&mock_driver.get());

    // Action
    sig_gen.testSignal();

    // Evalulate Result
    fakeit::Verify(Method(mock_driver,pulse)).Exactly(7);
    fakeit::VerifyNoOtherInvocations(mock_driver);
    CHECK(true);
}

TEST_CASE("testSignal() returns `E_DRIVER`, when pulse() returns an error during test sequence", "[testSignal][error][pulse_driver]") {
    // Setup
    fakeit::Mock<PulseDriver> mock_driver;
    fakeit::When(Method(mock_driver,pulse)).Return(0,0,0,0,0,0,0,1);
    SignalGenerator sig_gen(&mock_driver.get());

    // Action
    const int result = sig_gen.testSignal();

    // Evalulate Result
    CHECK(SignalGenerator::ErrorCode::E_DRIVER == static_cast<SignalGenerator::ErrorCode>(result));
}

TEST_CASE("testSignal() returns `SUCCESS`, when no errors occur", "[testSignal][error]") {
    // Setup
    fakeit::Mock<PulseDriver> mock_driver;
    fakeit::When(Method(mock_driver,pulse)).AlwaysReturn(0);
    SignalGenerator sig_gen(&mock_driver.get());

    // Action
    const int result = sig_gen.testSignal();

    // Evalulate Result
    CHECK(SignalGenerator::ErrorCode::SUCCESS == static_cast<SignalGenerator::ErrorCode>(result));
}
