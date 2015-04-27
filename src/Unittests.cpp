#include "Image.h"

#define CATCH_CONFIG_MAIN

#include <string>
#include <iostream>
#include <memory>

#include "catch.hpp"

MLLJET001::Image mainImg("shrek_rectangular.pgm");
MLLJET001::Image mask("donkey_mask.pgm");
MLLJET001::Image temp;

TEST_CASE("Test Adding", "[add]") {
    temp << "Tests/add_test.pgm";
    REQUIRE((mainImg + mask) == temp);
}

TEST_CASE("Test Subtracting", "[subtract]") {
    temp << "Tests/subtract_test.pgm";
    REQUIRE((mainImg - mask) == temp);
}

TEST_CASE("Test Inverting", "[invert]") {
    temp << "Tests/invert_test.pgm";
    REQUIRE(!mask == temp);
}

TEST_CASE("Test Masking", "[mask]") {
    temp << "Tests/mask_test.pgm";
    REQUIRE((mainImg / mask) == temp);
}

TEST_CASE("Test Threshold", "[threshold]") {
    temp << "Tests/200_threshold_test.pgm";
    REQUIRE((mainImg * 200) == temp);
}

TEST_CASE("Test Save", "[save]") {
    temp << "Tests/save_test.pgm";
    REQUIRE((mainImg + mask) == temp);
    (mainImg + mask) >> "Tests/save_test.pgm";
    temp << "Tests/save_test.pgm";
    REQUIRE((mainImg + mask) == temp);
}

TEST_CASE("Test Iterator", "[iterator]") {
    temp << "Tests/save_test.pgm";
    REQUIRE((mainImg + mask) == temp);
    MLLJET001::Image::ImageIterator tempIter = temp.begin();
    MLLJET001::Image temp2;
    temp2 = mainImg + mask;
    MLLJET001::Image::ImageIterator maskIter = temp2.begin();

    bool allEqual = true;
    while (tempIter != temp.end()) {
        if (*tempIter != *maskIter) {
            allEqual = false;
            break;
        }
        tempIter++;
        maskIter++;
    }
    REQUIRE(allEqual);
}
