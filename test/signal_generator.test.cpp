#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include <fakeit.hpp>

// Compile Command: g++ signal_generator.test.cpp ../src/signal_generator.cpp -I../src/ -I Catch2/single_include/ -I FakeIt/single_header/catch/

#include "signal_driver.hpp"
#include "signal_generator.hpp"

TEST_CASE("Sequences are 8 bits, prefixed with a 5-bit initialization sequence", "[signal_driver][preamble]") {
    // Setup
    fakeit::Mock<SignalDriver> mock_driver;
    fakeit::When(Method(mock_driver,pulse)).AlwaysReturn(0);
    SignalGenerator sig_gen(&mock_driver.get());

    // Action
    sig_gen.signal(0xAA);

    // Evalulate Result
    fakeit::Verify(Method(mock_driver,pulse)).Exactly(13);
    CHECK(true);
}

TEST_CASE("5-bit initialization sequence is `00010`", "[signal_driver][preamble]") {
    // Setup
    fakeit::Mock<SignalDriver> mock_driver;
    fakeit::When(Method(mock_driver,pulse)).AlwaysReturn(0);
    SignalGenerator sig_gen(&mock_driver.get());

    // Action
    sig_gen.signal(0x17);

    // Evalulate Result
    fakeit::Verify((Method(mock_driver,pulse).Using(0) * 3) + Method(mock_driver,pulse).Using(1) + Method(mock_driver,pulse).Using(0) + (Method(mock_driver,pulse).Using(fakeit::_) * 8)).Once();
    CHECK(true);
}

TEST_CASE("Sequences matches sequence parameter", "[signal_driver][sequence]") {
    // Setup
    fakeit::Mock<SignalDriver> mock_driver;
    fakeit::When(Method(mock_driver,pulse)).AlwaysReturn(0);
    SignalGenerator sig_gen(&mock_driver.get());

    // Action
    sig_gen.signal(0xAA);

    // Evalulate Result
    fakeit::Verify((Method(mock_driver,pulse).Using(fakeit::_) * 5) + ((Method(mock_driver,pulse).Using(1) + Method(mock_driver,pulse).Using(0)) * 4)).Once();
    CHECK(true);
}

TEST_CASE("Sequences longer than 8 bits will only use the bottom 8-bits", "[signal_driver][sequence]") {
    // Setup
    fakeit::Mock<SignalDriver> mock_driver;
    fakeit::When(Method(mock_driver,pulse)).AlwaysReturn(0);
    SignalGenerator sig_gen(&mock_driver.get());

    // Action
    sig_gen.signal(0xCC55FFAA);

    // Evalulate Result
    fakeit::Verify((Method(mock_driver,pulse).Using(fakeit::_) * 5) + ((Method(mock_driver,pulse).Using(1) + Method(mock_driver,pulse).Using(0)) * 4)).Once();
    CHECK(true);
}

TEST_CASE("Signal halts when `pulse` returns error during preamble", "[signal_driver][error][preamble]") {
    // Setup
    fakeit::Mock<SignalDriver> mock_driver;
    fakeit::When(Method(mock_driver,pulse)).Return(0,0,1);
    SignalGenerator sig_gen(&mock_driver.get());

    // Action
    sig_gen.signal(0xAA);

    // Evalulate Result
    fakeit::Verify(Method(mock_driver,pulse)).Exactly(3);
    CHECK(true);
}

TEST_CASE("Signal halts when `pulse` returns error during sequence", "[signal_driver][error]") {
    // Setup
    fakeit::Mock<SignalDriver> mock_driver;
    fakeit::When(Method(mock_driver,pulse)).Return(0,0,0,0,0,0,0,1);
    SignalGenerator sig_gen(&mock_driver.get());

    // Action
    sig_gen.signal(0xAA);

    // Evalulate Result
    fakeit::Verify(Method(mock_driver,pulse)).Exactly(8);
    CHECK(true);
}
