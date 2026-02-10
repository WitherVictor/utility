#include <gtest/gtest.h>

#include <roll_dice.hpp>

TEST(roll_dice_unittest, error_input) {
    EXPECT_EQ(roll_dice("d6"), "Invalid dice info");
    EXPECT_EQ(roll_dice("6d"), "Invalid dice info");
    EXPECT_EQ(roll_dice("123456789"), "Invalid dice info");
    EXPECT_EQ(roll_dice("!#@$%@^#$"), "Invalid dice info");
    EXPECT_EQ(roll_dice("dagmnoirj"), "Invalid dice info");
}