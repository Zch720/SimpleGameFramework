#include <gtest/gtest.h>

#include <glm/mat2x2.hpp>

#include "sgf/type/mat2.h"
#include "sgf/type/casting/cast_mat2.h"

class Mat2Suite: public testing::Test {
};

TEST_F(Mat2Suite, CreateEmpty) {
    sgf::type::Mat2 oMat;

    ASSERT_EQ(0, oMat[0].x);
    ASSERT_EQ(0, oMat[0].y);
    ASSERT_EQ(0, oMat[1].x);
    ASSERT_EQ(0, oMat[1].y);
}

TEST_F(Mat2Suite, CreateWithScale) {
    sgf::type::Mat2 oMat(2);

    ASSERT_EQ(2, oMat[0].x);
    ASSERT_EQ(0, oMat[0].y);
    ASSERT_EQ(0, oMat[1].x);
    ASSERT_EQ(2, oMat[1].y);
}

TEST_F(Mat2Suite, CreateWithColumns) {
    sgf::type::Mat2 oMat(
        sgf::type::Vec2(1, 2),
        sgf::type::Vec2(3, 4)
    );

    ASSERT_EQ(1, oMat[0].x);
    ASSERT_EQ(2, oMat[0].y);
    ASSERT_EQ(3, oMat[1].x);
    ASSERT_EQ(4, oMat[1].y);
}

TEST_F(Mat2Suite, CreateWithArray) {
    float arrVal[2][2] = {
        { 1, 2 },
        { 3, 4 }
    };
    sgf::type::Mat2 oMat(arrVal);

    ASSERT_EQ(1, oMat[0].x);
    ASSERT_EQ(2, oMat[0].y);
    ASSERT_EQ(3, oMat[1].x);
    ASSERT_EQ(4, oMat[1].y);
}

TEST_F(Mat2Suite, BracketGetter) {
    sgf::type::Mat2 oMat(
        sgf::type::Vec2(1, 2),
        sgf::type::Vec2(3, 4)
    );

    ASSERT_EQ(1, oMat[0].x);
    oMat[0].x = 100;
    ASSERT_EQ(100, oMat[0].x);
}

TEST_F(Mat2Suite, ConstBracketGetter) {
    const sgf::type::Mat2 oMat(
        sgf::type::Vec2(1, 2),
        sgf::type::Vec2(3, 4)
    );

    ASSERT_EQ(1, oMat[0].x);
    ASSERT_EQ(4, oMat[1].y);
}

TEST_F(Mat2Suite, PlusTwoMat) {
    sgf::type::Mat2 oMat1(
        sgf::type::Vec2(1, 2),
        sgf::type::Vec2(3, 4)
    );
    sgf::type::Mat2 oMat2(
        sgf::type::Vec2(2, 3),
        sgf::type::Vec2(4, 5)
    );

    oMat1.plus(oMat2);

    ASSERT_EQ(3, oMat1[0].x);
    ASSERT_EQ(5, oMat1[0].y);
    ASSERT_EQ(7, oMat1[1].x);
    ASSERT_EQ(9, oMat1[1].y);
}

TEST_F(Mat2Suite, PlusMatItself) {
    sgf::type::Mat2 oMat(
        sgf::type::Vec2(1, 2),
        sgf::type::Vec2(3, 4)
    );

    oMat.plus(oMat);

    ASSERT_EQ(2, oMat[0].x);
    ASSERT_EQ(4, oMat[0].y);
    ASSERT_EQ(6, oMat[1].x);
    ASSERT_EQ(8, oMat[1].y);
}

TEST_F(Mat2Suite, MinusTwoMat) {
    sgf::type::Mat2 oMat1(
        sgf::type::Vec2(1, 2),
        sgf::type::Vec2(3, 4)
    );
    sgf::type::Mat2 oMat2(
        sgf::type::Vec2(2, 3),
        sgf::type::Vec2(4, 5)
    );

    oMat1.minus(oMat2);

    ASSERT_EQ(-1, oMat1[0].x);
    ASSERT_EQ(-1, oMat1[0].y);
    ASSERT_EQ(-1, oMat1[1].x);
    ASSERT_EQ(-1, oMat1[1].y);
}

TEST_F(Mat2Suite, MinusMatItself) {
    sgf::type::Mat2 oMat(
        sgf::type::Vec2(1, 2),
        sgf::type::Vec2(3, 4)
    );

    oMat.minus(oMat);

    ASSERT_EQ(0, oMat[0].x);
    ASSERT_EQ(0, oMat[0].y);
    ASSERT_EQ(0, oMat[1].x);
    ASSERT_EQ(0, oMat[1].y);
}

TEST_F(Mat2Suite, MultiplyMat) {
    sgf::type::Mat2 oMat(
        sgf::type::Vec2(1, 2),
        sgf::type::Vec2(3, 4)
    );

    oMat.multiply(2);

    ASSERT_EQ(2, oMat[0].x);
    ASSERT_EQ(4, oMat[0].y);
    ASSERT_EQ(6, oMat[1].x);
    ASSERT_EQ(8, oMat[1].y);
}

TEST_F(Mat2Suite, DivideMat) {
    sgf::type::Mat2 oMat(
        sgf::type::Vec2(1, 2),
        sgf::type::Vec2(3, 4)
    );

    oMat.divide(1);

    ASSERT_FLOAT_EQ(1.0, oMat[0].x);
}

TEST_F(Mat2Suite, TwoEqualItSelf) {
    sgf::type::Mat2 oMat(
        sgf::type::Vec2(1, 2),
        sgf::type::Vec2(3, 4)
    );
    ASSERT_TRUE(oMat.equal(oMat));
}

TEST_F(Mat2Suite, TwoEqualMat) {
    sgf::type::Mat2 oMat1(
        sgf::type::Vec2(1, 2),
        sgf::type::Vec2(3, 4)
    );
    sgf::type::Mat2 oMat2(
        sgf::type::Vec2(1, 2),
        sgf::type::Vec2(3, 4)
    );
    ASSERT_TRUE(oMat1.equal(oMat2));
}

TEST_F(Mat2Suite, TwoNonEqualMat) {
    sgf::type::Mat2 oMat1(
        sgf::type::Vec2(1, 2),
        sgf::type::Vec2(3, 4)
    );
    sgf::type::Mat2 oMat2(
        sgf::type::Vec2(2, 3),
        sgf::type::Vec2(4, 5)
    );
    ASSERT_FALSE(oMat1.equal(oMat2));
}

TEST_F(Mat2Suite, CastToGLMMat) {
    sgf::type::Mat2 oSGFMat(
        sgf::type::Vec2(1, 2),
        sgf::type::Vec2(3, 4)
    );
    glm::mat2& rGLMMat = sgf::type::toGLM(oSGFMat);

    ASSERT_EQ(1, rGLMMat[0].x);
    ASSERT_EQ(4, rGLMMat[1].y);
}

TEST_F(Mat2Suite, CastToGLMMatIsSameAddress) {
    sgf::type::Mat2 oSGFMat(
        sgf::type::Vec2(1, 2),
        sgf::type::Vec2(3, 4)
    );
    glm::mat2& rGLMMat = sgf::type::toGLM(oSGFMat);

    rGLMMat[0].x = 99;
    ASSERT_EQ(99, oSGFMat[0].x);
}

TEST_F(Mat2Suite, CastFromGLMMat) {
    glm::mat2 oGLMMat(1, 2, 3, 4);
    sgf::type::Mat2& rSGFMat = sgf::type::toSGF(oGLMMat);

    ASSERT_EQ(1, rSGFMat[0].x);
    ASSERT_EQ(4, rSGFMat[1].y);
}

TEST_F(Mat2Suite, CastFromGLMMatIsSameAddress) {
    glm::mat2 oGLMMat(1, 2, 3, 4);
    sgf::type::Mat2& rSGFMat = sgf::type::toSGF(oGLMMat);

    rSGFMat[0].x = 99;
    ASSERT_EQ(99, oGLMMat[0].x);
}
