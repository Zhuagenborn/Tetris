
#include "tetromino.h"

#include <gtest/gtest.h>

using namespace testing;


TEST(TetrominoTest, Filled) {
    tetromino::O o;
    EXPECT_TRUE(o.Filled({0, 0}));
    EXPECT_TRUE(o.Filled({0, 1}));
    EXPECT_TRUE(o.Filled({1, 0}));
    EXPECT_TRUE(o.Filled({1, 1}));

    EXPECT_FALSE(o.Filled({o.GetHeight() + 1, o.GetWidth() + 1}));
}