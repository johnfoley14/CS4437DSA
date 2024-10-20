#include <gtest/gtest.h>
#include "DynamicArray.h"

TEST(DynamicArrayTest, DynamicArrayCreation)
{
    DynamicArray<std::string> *dynamicArray = new DynamicArray<std::string>();
    ASSERT_NE(dynamicArray, nullptr);
    delete dynamicArray;
}

TEST(DynamicArrayTest, DynamicArrayCreationWithInt)
{
    DynamicArray<int> *dynamicArray = new DynamicArray<int>();
    ASSERT_NE(dynamicArray, nullptr);
    delete dynamicArray;
}

TEST(DynamicArrayTest, DynamicArrayDeletion)
{
    DynamicArray<std::string> *dynamicArray = new DynamicArray<std::string>();
    delete dynamicArray;
}

TEST(DynamicArrayTest, AddElementToDynamicArray)
{
    DynamicArray<std::string> *dynamicArray = new DynamicArray<std::string>();
    dynamicArray->add("hello");
    EXPECT_EQ(dynamicArray->getSize(), 1);
    delete dynamicArray;
}

TEST(DynamicArrayTest, DynamicArrayResize)
{
    DynamicArray<std::string> *dynamicArray = new DynamicArray<std::string>(1);
    dynamicArray->add("hello");
    dynamicArray->add("world");
    EXPECT_EQ(dynamicArray->getSize(), 2);
    delete dynamicArray;
}

TEST(DynamicArrayTest, DynamicArrayEquality)
{
    DynamicArray<std::string> *dynamicArray1 = new DynamicArray<std::string>();
    dynamicArray1->add("hello");
    dynamicArray1->add("world");

    DynamicArray<std::string> *dynamicArray2 = new DynamicArray<std::string>();
    dynamicArray2->add("hello");
    dynamicArray2->add("world");

    EXPECT_EQ(*dynamicArray1, *dynamicArray2);
    delete dynamicArray1;
    delete dynamicArray2;
}
