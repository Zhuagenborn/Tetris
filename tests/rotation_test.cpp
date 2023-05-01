
#include "rotation.h"

#include <gtest/gtest.h>

using namespace testing;


TEST(RotationTest, Angle) {
    EXPECT_EQ(RotateAngleLeft(Angle::Degree0), Angle::Degree90);
    EXPECT_EQ(RotateAngleLeft(Angle::Degree90), Angle::Degree180);
    EXPECT_EQ(RotateAngleLeft(Angle::Degree180), Angle::Degree270);
    EXPECT_EQ(RotateAngleLeft(Angle::Degree270), Angle::Degree0);

    EXPECT_EQ(RotateAngleRight(Angle::Degree0), Angle::Degree270);
    EXPECT_EQ(RotateAngleRight(Angle::Degree270), Angle::Degree180);
    EXPECT_EQ(RotateAngleRight(Angle::Degree180), Angle::Degree90);
    EXPECT_EQ(RotateAngleRight(Angle::Degree90), Angle::Degree0);
}