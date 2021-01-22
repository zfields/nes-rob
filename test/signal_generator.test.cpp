#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include <fakeit.hpp>

// Compile Command: g++ signal_generator.test.cpp ../src/signal_generator.cpp  -I Catch2/single_include/ -I../src/ -I FakeIt/single_header/catch/

#include "signal_driver.hpp"
#include "signal_generator.hpp"

TEST_CASE("Command sequences are prefixed with a 5-bit initialization sequence", "[signal_driver][preamble]") {
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

//TEST_CASE("5-bit initialization sequence is `00010`", "[signal_driver][preamble]") {
//TEST_CASE("Command sequences matches signal parameter", "[signal_driver][preamble]") {
//TEST_CASE("Command sequences halts when `pulse` returns error", "[signal_driver][error]") {
