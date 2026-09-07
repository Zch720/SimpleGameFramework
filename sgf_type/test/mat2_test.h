#include <gtest/gtest.h>
#include "sgf/type/mat2.h"
#include "sgf/type/casting/cast_mat2.h"

class Mat2Suite: public testing::Test {
};

TEST_F(Mat2Suite, CastSgfMat2ToGlmMat2) {
    sgf::Mat2 m {{ 1, 2 }, { 3, 4 }};

    glm::mat2 glmM = sgf::toGlm(m);

    ASSERT_EQ(1, glmM[0][0]);
    ASSERT_EQ(2, glmM[0][1]);
    ASSERT_EQ(3, glmM[1][0]);
    ASSERT_EQ(4, glmM[1][1]);
}

TEST_F(Mat2Suite, CastGlmMat2ToSgfMat2) {
    glm::mat2 m {{ 1, 2 }, { 3, 4 }};

    sgf::Mat2 sgfM = sgf::toSgf(m);

    ASSERT_EQ(1, sgfM[0][0]);
    ASSERT_EQ(2, sgfM[0][1]);
    ASSERT_EQ(3, sgfM[1][0]);
    ASSERT_EQ(4, sgfM[1][1]);
}
