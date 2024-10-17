#include <gtest/gtest.h>

#include "RelevanceFunction.h"  // Assuming calculateBonusMarks is declared in this header

// Test case for a distance of 1 (should return 5)
TEST(CalculateBonusMarksTest, DistanceOne) {
    EXPECT_EQ(calculateBonusMarks(10, 11), 5);
    EXPECT_EQ(calculateBonusMarks(100, 101), 5);
}

// Test case for a distance of 2 (should return 4)
TEST(CalculateBonusMarksTest, DistanceTwo) {
    EXPECT_EQ(calculateBonusMarks(20, 18), 4);
    EXPECT_EQ(calculateBonusMarks(5, 7), 4);
}

// Test case for a distance of 3 (should return 3)
TEST(CalculateBonusMarksTest, DistanceThree) {
    EXPECT_EQ(calculateBonusMarks(30, 27), 3);
    EXPECT_EQ(calculateBonusMarks(50, 47), 3);
}

// Test case for a distance of 4 (should return 2)
TEST(CalculateBonusMarksTest, DistanceFour) {
    EXPECT_EQ(calculateBonusMarks(40, 36), 2);
    EXPECT_EQ(calculateBonusMarks(90, 86), 2);
}

// Test case for a distance of 5 (should return 1)
TEST(CalculateBonusMarksTest, DistanceFive) {
    EXPECT_EQ(calculateBonusMarks(25, 30), 1);
    EXPECT_EQ(calculateBonusMarks(60, 55), 1);
}

// Test case for distances greater than 5 (should return 0)
TEST(CalculateBonusMarksTest, DistanceGreaterThanFive) {
    EXPECT_EQ(calculateBonusMarks(10, 20), 0);
    EXPECT_EQ(calculateBonusMarks(100, 106), 0);
}

// Test case for same positions (should return 0)
TEST(CalculateBonusMarksTest, SamePosition) {
    EXPECT_EQ(calculateBonusMarks(10, 10), 0);
    EXPECT_EQ(calculateBonusMarks(100, 100), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
