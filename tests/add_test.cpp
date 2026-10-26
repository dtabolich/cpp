#include "add.hpp"

#include <gtest/gtest.h>

TEST(AddTest, AddsPositiveNumbers) {
  EXPECT_EQ(cpp::add(2, 3), 5);
}

TEST(AddTest, AddsNegativeNumbers) {
  EXPECT_EQ(cpp::add(-1, -2), -3);
}
