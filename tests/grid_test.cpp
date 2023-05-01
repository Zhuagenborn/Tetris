
#include "grid.h"

#include <gtest/gtest.h>

using namespace testing;


TEST(GridTest, Move) {
    /*
        . . . .
        . . . .
        . . . .
        . . . .
    */
    constexpr std::size_t width {4};
    constexpr std::size_t height {4};
    Grid grid(width, height);

    /*
        O O . .
        O O . .
        . . . .
        . . . .
    */
    ASSERT_TRUE(
        grid.PushTetromino(std::make_unique<tetromino::O>(), Point {0, 0}));

    EXPECT_FALSE(grid.MoveTetrominoToLeft());

    /*
        . O O .
        . O O .
        . . . .
        . . . .
    */
    ASSERT_TRUE(grid.MoveTetrominoToRight());

    /*
        . . O O
        . . O O
        . . . .
        . . . .
    */
    ASSERT_TRUE(grid.MoveTetrominoToRight());

    EXPECT_FALSE(grid.MoveTetrominoToRight());

    /*
        . . . .
        . . O O
        . . O O
        . . . .
    */
    std::size_t cleared_line_count {0};
    ASSERT_TRUE(grid.TetrominoDescend(cleared_line_count));
    EXPECT_EQ(cleared_line_count, 0);

    /*
        . . . .
        . . . .
        . . O O
        . . O O
    */
    ASSERT_TRUE(grid.TetrominoDescend(cleared_line_count));
    EXPECT_EQ(cleared_line_count, 0);

    EXPECT_FALSE(grid.TetrominoDescend(cleared_line_count));
    EXPECT_EQ(cleared_line_count, 0);
}

TEST(GridTest, Rotate) {
    /*
        . . . .
        . . . .
        . . . .
        . . . .
    */
    constexpr std::size_t width {4};
    constexpr std::size_t height {4};
    Grid grid(width, height);

    /*
        O . . .
        O . . .
        O . . .
        O . . .
    */
    ASSERT_TRUE(
        grid.PushTetromino(std::make_unique<tetromino::I>(), Point {0, 0}));

    /*
        O O O O
        . . . .
        . . . .
        . . . .
    */
    ASSERT_TRUE(grid.RotateTetrominoRight());

    /*
        O . . .
        O . . .
        O . . .
        O . . .
    */
    ASSERT_TRUE(grid.RotateTetrominoRight());

    /*
        . O . .
        . O . .
        . O . .
        . O . .
    */
    ASSERT_TRUE(grid.MoveTetrominoToRight());

    EXPECT_FALSE(grid.RotateTetrominoLeft());
}

TEST(GridTest, ClearLines) {
    /*
        . . . .
        . . . .
        . . . .
        . . . .
    */
    constexpr std::size_t width {4};
    constexpr std::size_t height {4};
    Grid grid(width, height);

    /*
        O O . .
        O O . .
        . . . .
        . . . .
    */
    ASSERT_TRUE(
        grid.PushTetromino(std::make_unique<tetromino::O>(), Point {0, 0}));

    /*
        . . . .
        . . . .
        O O . .
        O O . .
    */
    std::size_t cleared_line_count {0};
    ASSERT_TRUE(grid.TetrominoDescend(cleared_line_count));
    EXPECT_EQ(cleared_line_count, 0);

    ASSERT_TRUE(grid.TetrominoDescend(cleared_line_count));
    EXPECT_EQ(cleared_line_count, 0);

    EXPECT_FALSE(grid.TetrominoDescend(cleared_line_count));
    EXPECT_EQ(cleared_line_count, 0);

    /*
        . . O O
        . . O O
        O O . .
        O O . .
    */
    ASSERT_TRUE(
        grid.PushTetromino(std::make_unique<tetromino::O>(), Point {2, 0}));

    /*
        . . . .
        . . O O
        O O O O
        O O . .
    */
    ASSERT_TRUE(grid.TetrominoDescend(cleared_line_count));
    EXPECT_EQ(cleared_line_count, 0);

    /*
        . . . .
        . . . .
        O O O O
        O O O O
    */
    ASSERT_TRUE(grid.TetrominoDescend(cleared_line_count));
    EXPECT_EQ(cleared_line_count, 0);

    /*
        . . . .
        . . . .
        . . . .
        . . . .
    */
    EXPECT_FALSE(grid.TetrominoDescend(cleared_line_count));
    EXPECT_EQ(cleared_line_count, 2);
}