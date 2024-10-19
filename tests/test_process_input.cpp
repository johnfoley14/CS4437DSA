#include <gtest/gtest.h>
#include <vector>
#include "ProcessInput.h"

// Test case 1: Basic test with delimiters
TEST(SanitizeLineTest, BasicTest) {
    LinkedList<string> expected;
    expected.append("Hello");
    expected.append("world");
    expected.append("test");

    LinkedList<string> result = sanitizeLine("Hello-world—test");

    EXPECT_EQ(result, expected);
}

// Test case 2: String with multiple spaces and delimiters
TEST(SanitizeLineTest, DelimitersTest) {
    LinkedList<string> expected;
    expected.append("Hello");
    expected.append("world");
    expected.append("test");
    expected.append("string");

    LinkedList<string> result = sanitizeLine("Hello - world — test-string");

    EXPECT_EQ(result, expected);
}

// Test case 3: String with no delimiters
TEST(SanitizeLineTest, NoDelimitersTest) {
    LinkedList<string> expected;
    expected.append("HelloWorldTest");

    LinkedList<string> result = sanitizeLine("HelloWorldTest");

    EXPECT_EQ(result, expected);
}

// Test case 4: Empty string
TEST(SanitizeLineTest, EmptyStringTest) {
    LinkedList<string> expected; // No elements

    LinkedList<string> result = sanitizeLine("");

    EXPECT_EQ(result, expected);
}

// Test case 5: String with consecutive delimiters
TEST(SanitizeLineTest, ConsecutiveDelimitersTest) {
    LinkedList<string> expected;
    expected.append("Hello");
    expected.append("world");
    expected.append("test");

    LinkedList<string> result = sanitizeLine("Hello--world——test");

    EXPECT_EQ(result, expected);
}

// Test case 6: String with only delimiters
TEST(SanitizeLineTest, OnlyDelimitersTest) {
    LinkedList<string> expected; // No elements

    LinkedList<string> result = sanitizeLine("- —  — -");

    EXPECT_EQ(result, expected);
}