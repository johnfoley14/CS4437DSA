#include <gtest/gtest.h>
#include "add.h"

// Basic test to check if the add function works correctly
TEST(AddFunctionTest, PositiveNumbers) {
    EXPECT_EQ(add(2, 3), 5);
}

TEST(AddFunctionTest, NegativeNumbers) {
    EXPECT_EQ(add(-2, -3), -5);
}

TEST(AddFunctionTest, MixedNumbers) {
    EXPECT_EQ(add(-2, 3), 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
