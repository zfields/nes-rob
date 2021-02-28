#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

// Compile Command: g++ NesRob.test.cpp -Wall -Wpedantic -I ../src/ -I Catch2/single_include/

#include "NesRob.h"

TEST_CASE("Command Enum Class Verification", "[commands]") {
    CHECK(static_cast<int>(NesRob::Command::LEFT) == 0xBA);
    CHECK(static_cast<int>(NesRob::Command::RIGHT) == 0xEA);
    CHECK(static_cast<int>(NesRob::Command::DOWN) == 0xAE);
    CHECK(static_cast<int>(NesRob::Command::DOWN_2) == 0xFB);
    CHECK(static_cast<int>(NesRob::Command::UP) == 0xFA);
    CHECK(static_cast<int>(NesRob::Command::UP_2) == 0xBB);
    CHECK(static_cast<int>(NesRob::Command::CLOSE) == 0xBE);
    CHECK(static_cast<int>(NesRob::Command::OPEN) == 0xEE);
    CHECK(static_cast<int>(NesRob::Command::LED_DISABLE) == 0xAA);
    CHECK(static_cast<int>(NesRob::Command::LED_ENABLE) == 0xEB);
    CHECK(static_cast<int>(NesRob::Command::RECALIBRATE) == 0xAB);
}
