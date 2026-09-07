#include <gtest/gtest.h>
#include "sgf/type/mat2x3.h"
#include "sgf/type/casting/cast_mat2x3.h"

class Mat2x3Suite: public testing::Test {
};

TEST_F(Mat2x3Suite, CastSgfMat2x3ToGlmMat2x3) {
    sgf::Mat2x3 m {{ 1, 2, 3 }, { 3, 4, 5 }};

    glm::mat2x3 glmM = sgf::toGlm(m);

    ASSERT_EQ(1, glmM[0][0]);
    ASSERT_EQ(2, glmM[0][1]);
    ASSERT_EQ(3, glmM[0][2]);
    ASSERT_EQ(3, glmM[1][0]);
    ASSERT_EQ(4, glmM[1][1]);
    ASSERT_EQ(5, glmM[1][2]);
}

TEST_F(Mat2x3Suite, CastGlmMat2x3ToSgfMat2x3) {
    glm::mat2x3 m {{ 1, 2, 3 }, { 3, 4, 5 }};

    sgf::Mat2x3 sgfM = sgf::toSgf(m);

    ASSERT_EQ(1, sgfM[0][0]);
    ASSERT_EQ(2, sgfM[0][1]);
    ASSERT_EQ(3, sgfM[0][2]);
    ASSERT_EQ(3, sgfM[1][0]);
    ASSERT_EQ(4, sgfM[1][1]);
    ASSERT_EQ(5, sgfM[1][2]);
}
