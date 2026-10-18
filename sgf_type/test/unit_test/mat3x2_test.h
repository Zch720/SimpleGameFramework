#include <gtest/gtest.h>

#include <glm/mat3x2.hpp>

#include "sgf/type/mat3x2.h"
#include "sgf/type/casting/cast_mat3x2.h"

class Mat3x2Suite: public testing::Test {
};

TEST_F(Mat3x2Suite, CreateEmpty) {
    sgf::type::Mat3x2 oMat;

    ASSERT_EQ(0, oMat[0].x);
    ASSERT_EQ(0, oMat[0].y);
    ASSERT_EQ(0, oMat[1].x);
    ASSERT_EQ(0, oMat[1].y);
    ASSERT_EQ(0, oMat[2].x);
    ASSERT_EQ(0, oMat[2].y);
}

TEST_F(Mat3x2Suite, CreateWithColumns) {
    sgf::type::Mat3x2 oMat(
        sgf::type::Vec2(1, 2),
        sgf::type::Vec2(3, 4),
        sgf::type::Vec2(5, 6)
    );

    ASSERT_EQ(1, oMat[0].x);
    ASSERT_EQ(2, oMat[0].y);
    ASSERT_EQ(3, oMat[1].x);
    ASSERT_EQ(4, oMat[1].y);
    ASSERT_EQ(5, oMat[2].x);
    ASSERT_EQ(6, oMat[2].y);
}

TEST_F(Mat3x2Suite, CreateWithArray) {
    float arrVal[3][2] = {
        { 1, 2 },
        { 3, 4 },
        { 5, 6 }
    };
    sgf::type::Mat3x2 oMat(arrVal);

    ASSERT_EQ(1, oMat[0].x);
    ASSERT_EQ(2, oMat[0].y);
    ASSERT_EQ(3, oMat[1].x);
    ASSERT_EQ(4, oMat[1].y);
    ASSERT_EQ(5, oMat[2].x);
    ASSERT_EQ(6, oMat[2].y);
}

TEST_F(Mat3x2Suite, BracketGetter) {
    sgf::type::Mat3x2 oMat(
        sgf::type::Vec2(1, 2),
        sgf::type::Vec2(3, 4),
        sgf::type::Vec2(5, 6)
    );

    ASSERT_EQ(1, oMat[0].x);
    oMat[0].x = 100;
    ASSERT_EQ(100, oMat[0].x);
}

TEST_F(Mat3x2Suite, ConstBracketGetter) {
    const sgf::type::Mat3x2 oMat(
        sgf::type::Vec2(1, 2),
        sgf::type::Vec2(3, 4),
        sgf::type::Vec2(5, 6)
    );

    ASSERT_EQ(1, oMat[0].x);
}

TEST_F(Mat3x2Suite, PlusTwoMat) {
    sgf::type::Mat3x2 oMat1(
        sgf::type::Vec2(1, 2),
        sgf::type::Vec2(3, 4),
        sgf::type::Vec2(5, 6)
    );
    sgf::type::Mat3x2 oMat2(
        sgf::type::Vec2(2, 3),
        sgf::type::Vec2(4, 5),
        sgf::type::Vec2(6, 7)
    );

    oMat1.plus(oMat2);

    ASSERT_EQ(3, oMat1[0].x);
    ASSERT_EQ(5, oMat1[0].y);
    ASSERT_EQ(7, oMat1[1].x);
    ASSERT_EQ(9, oMat1[1].y);
    ASSERT_EQ(11, oMat1[2].x);
    ASSERT_EQ(13, oMat1[2].y);
}

TEST_F(Mat3x2Suite, PlusMatItself) {
    sgf::type::Mat3x2 oMat(
        sgf::type::Vec2(1, 2),
        sgf::type::Vec2(3, 4),
        sgf::type::Vec2(5, 6)
    );

    oMat.plus(oMat);

    ASSERT_EQ(2, oMat[0].x);
    ASSERT_EQ(4, oMat[0].y);
    ASSERT_EQ(6, oMat[1].x);
    ASSERT_EQ(8, oMat[1].y);
    ASSERT_EQ(10, oMat[2].x);
    ASSERT_EQ(12, oMat[2].y);
}

TEST_F(Mat3x2Suite, MinusTwoMat) {
    sgf::type::Mat3x2 oMat1(
        sgf::type::Vec2(1, 2),
        sgf::type::Vec2(3, 4),
        sgf::type::Vec2(5, 6)
    );
    sgf::type::Mat3x2 oMat2(
        sgf::type::Vec2(2, 3),
        sgf::type::Vec2(4, 5),
        sgf::type::Vec2(6, 7)
    );

    oMat1.minus(oMat2);

    ASSERT_EQ(-1, oMat1[0].x);
    ASSERT_EQ(-1, oMat1[0].y);
    ASSERT_EQ(-1, oMat1[1].x);
    ASSERT_EQ(-1, oMat1[1].y);
    ASSERT_EQ(-1, oMat1[2].x);
    ASSERT_EQ(-1, oMat1[2].y);
}

TEST_F(Mat3x2Suite, MinusMatItself) {
    sgf::type::Mat3x2 oMat(
        sgf::type::Vec2(1, 2),
        sgf::type::Vec2(3, 4),
        sgf::type::Vec2(5, 6)
    );

    oMat.minus(oMat);

    ASSERT_EQ(0, oMat[0].x);
    ASSERT_EQ(0, oMat[0].y);
    ASSERT_EQ(0, oMat[1].x);
    ASSERT_EQ(0, oMat[1].y);
    ASSERT_EQ(0, oMat[2].x);
    ASSERT_EQ(0, oMat[2].y);
}

TEST_F(Mat3x2Suite, MultiplyMat) {
    sgf::type::Mat3x2 oMat(
        sgf::type::Vec2(1, 2),
        sgf::type::Vec2(3, 4),
        sgf::type::Vec2(5, 6)
    );

    oMat.multiply(2);

    ASSERT_EQ(2, oMat[0].x);
    ASSERT_EQ(4, oMat[0].y);
    ASSERT_EQ(6, oMat[1].x);
    ASSERT_EQ(8, oMat[1].y);
    ASSERT_EQ(10, oMat[2].x);
    ASSERT_EQ(12, oMat[2].y);
}

TEST_F(Mat3x2Suite, DivideMat) {
    sgf::type::Mat3x2 oMat(
        sgf::type::Vec2(1, 2),
        sgf::type::Vec2(3, 4),
        sgf::type::Vec2(5, 6)
    );

    oMat.divide(1);

    ASSERT_FLOAT_EQ(1.0, oMat[0].x);
}

TEST_F(Mat3x2Suite, TwoEqualItSelf) {
    sgf::type::Mat3x2 oMat(
        sgf::type::Vec2(1, 2),
        sgf::type::Vec2(3, 4),
        sgf::type::Vec2(5, 6)
    );
    ASSERT_TRUE(oMat.equal(oMat));
}

TEST_F(Mat3x2Suite, TwoEqualMat) {
    sgf::type::Mat3x2 oMat1(
        sgf::type::Vec2(1, 2),
        sgf::type::Vec2(3, 4),
        sgf::type::Vec2(5, 6)
    );
    sgf::type::Mat3x2 oMat2(
        sgf::type::Vec2(1, 2),
        sgf::type::Vec2(3, 4),
        sgf::type::Vec2(5, 6)
    );
    ASSERT_TRUE(oMat1.equal(oMat2));
}

TEST_F(Mat3x2Suite, TwoNonEqualMat) {
    sgf::type::Mat3x2 oMat1(
        sgf::type::Vec2(1, 2),
        sgf::type::Vec2(3, 4),
        sgf::type::Vec2(5, 6)
    );
    sgf::type::Mat3x2 oMat2(
        sgf::type::Vec2(2, 3),
        sgf::type::Vec2(4, 5),
        sgf::type::Vec2(6, 7)
    );
    ASSERT_FALSE(oMat1.equal(oMat2));
}

TEST_F(Mat3x2Suite, CastToGLMMat) {
    sgf::type::Mat3x2 oSGFMat(
        sgf::type::Vec2(1, 2),
        sgf::type::Vec2(3, 4),
        sgf::type::Vec2(5, 6)
    );
    glm::mat3x2& rGLMMat = sgf::type::toGLM(oSGFMat);

    ASSERT_EQ(1, rGLMMat[0].x);
}

TEST_F(Mat3x2Suite, CastToGLMMatIsSameAddress) {
    sgf::type::Mat3x2 oSGFMat(
        sgf::type::Vec2(1, 2),
        sgf::type::Vec2(3, 4),
        sgf::type::Vec2(5, 6)
    );
    glm::mat3x2& rGLMMat = sgf::type::toGLM(oSGFMat);

    rGLMMat[0].x = 99;
    ASSERT_EQ(99, oSGFMat[0].x);
}

TEST_F(Mat3x2Suite, CastFromGLMMat) {
    glm::mat3x2 oGLMMat(1, 2, 3, 4, 5, 6);
    sgf::type::Mat3x2& rSGFMat = sgf::type::toSGF(oGLMMat);

    ASSERT_EQ(1, rSGFMat[0].x);
}

TEST_F(Mat3x2Suite, CastFromGLMMatIsSameAddress) {
    glm::mat3x2 oGLMMat(1, 2, 3, 4, 5, 6);
    sgf::type::Mat3x2& rSGFMat = sgf::type::toSGF(oGLMMat);

    rSGFMat[0].x = 99;
    ASSERT_EQ(99, oGLMMat[0].x);
}
