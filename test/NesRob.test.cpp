#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch2/catch.hpp"

// Compile Command: g++ NesRob.test.cpp -I Catch2/single_include/ -I../src/

#include "NesRob.h"

TEST_CASE("Command Enum Class Verification", "[commands]") {
    CHECK(static_cast<int>(NesRob::Command::CALIBRATE_MOTORS) == 0xAB);
    CHECK(static_cast<int>(NesRob::Command::TEST_LED) == 0xEB);
    CHECK(static_cast<int>(NesRob::Command::ARMS_LEFT) == 0xBA);
    CHECK(static_cast<int>(NesRob::Command::ARMS_RIGHT) == 0xEA);
    CHECK(static_cast<int>(NesRob::Command::ARMS_LOWER) == 0xAE);
    CHECK(static_cast<int>(NesRob::Command::ARMS_LOWER_2) == 0xFB);
    CHECK(static_cast<int>(NesRob::Command::ARMS_RAISE) == 0xFA);
    CHECK(static_cast<int>(NesRob::Command::ARMS_RAISE_2) == 0xBB);
    CHECK(static_cast<int>(NesRob::Command::HANDS_CLOSE) == 0xBE);
    CHECK(static_cast<int>(NesRob::Command::HANDS_OPEN) == 0xEE);
}