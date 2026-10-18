#include <gtest/gtest.h>

#include <glm/mat3x4.hpp>

#include "sgf/type/mat3x4.h"
#include "sgf/type/casting/cast_mat3x4.h"

class Mat3x4Suite: public testing::Test {
};

TEST_F(Mat3x4Suite, CreateEmpty) {
    sgf::type::Mat3x4 oMat;

    ASSERT_EQ(0, oMat[0].x);
    ASSERT_EQ(0, oMat[0].y);
    ASSERT_EQ(0, oMat[0].z);
    ASSERT_EQ(0, oMat[0].w);
    ASSERT_EQ(0, oMat[1].x);
    ASSERT_EQ(0, oMat[1].y);
    ASSERT_EQ(0, oMat[1].z);
    ASSERT_EQ(0, oMat[1].w);
    ASSERT_EQ(0, oMat[2].x);
    ASSERT_EQ(0, oMat[2].y);
    ASSERT_EQ(0, oMat[2].z);
    ASSERT_EQ(0, oMat[2].w);
}

TEST_F(Mat3x4Suite, CreateWithColumns) {
    sgf::type::Mat3x4 oMat(
        sgf::type::Vec4(1, 2, 3, 4),
        sgf::type::Vec4(5, 6, 7, 8),
        sgf::type::Vec4(9, 10, 11, 12)
    );

    ASSERT_EQ(1, oMat[0].x);
    ASSERT_EQ(2, oMat[0].y);
    ASSERT_EQ(3, oMat[0].z);
    ASSERT_EQ(4, oMat[0].w);
    ASSERT_EQ(5, oMat[1].x);
    ASSERT_EQ(6, oMat[1].y);
    ASSERT_EQ(7, oMat[1].z);
    ASSERT_EQ(8, oMat[1].w);
    ASSERT_EQ(9, oMat[2].x);
    ASSERT_EQ(10, oMat[2].y);
    ASSERT_EQ(11, oMat[2].z);
    ASSERT_EQ(12, oMat[2].w);
}

TEST_F(Mat3x4Suite, CreateWithArray) {
    float arrVal[3][4] = {
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 }
    };
    sgf::type::Mat3x4 oMat(arrVal);

    ASSERT_EQ(1, oMat[0].x);
    ASSERT_EQ(2, oMat[0].y);
    ASSERT_EQ(3, oMat[0].z);
    ASSERT_EQ(4, oMat[0].w);
    ASSERT_EQ(5, oMat[1].x);
    ASSERT_EQ(6, oMat[1].y);
    ASSERT_EQ(7, oMat[1].z);
    ASSERT_EQ(8, oMat[1].w);
    ASSERT_EQ(9, oMat[2].x);
    ASSERT_EQ(10, oMat[2].y);
    ASSERT_EQ(11, oMat[2].z);
    ASSERT_EQ(12, oMat[2].w);
}

TEST_F(Mat3x4Suite, BracketGetter) {
    sgf::type::Mat3x4 oMat(
        sgf::type::Vec4(1, 2, 3, 4),
        sgf::type::Vec4(5, 6, 7, 8),
        sgf::type::Vec4(9, 10, 11, 12)
    );

    ASSERT_EQ(1, oMat[0].x);
    oMat[0].x = 100;
    ASSERT_EQ(100, oMat[0].x);
}

TEST_F(Mat3x4Suite, ConstBracketGetter) {
    const sgf::type::Mat3x4 oMat(
        sgf::type::Vec4(1, 2, 3, 4),
        sgf::type::Vec4(5, 6, 7, 8),
        sgf::type::Vec4(9, 10, 11, 12)
    );

    ASSERT_EQ(1, oMat[0].x);
}

TEST_F(Mat3x4Suite, PlusTwoMat) {
    sgf::type::Mat3x4 oMat1(
        sgf::type::Vec4(1, 2, 3, 4),
        sgf::type::Vec4(5, 6, 7, 8),
        sgf::type::Vec4(9, 10, 11, 12)
    );
    sgf::type::Mat3x4 oMat2(
        sgf::type::Vec4(2, 3, 4, 5),
        sgf::type::Vec4(6, 7, 8, 9),
        sgf::type::Vec4(10, 11, 12, 13)
    );

    oMat1.plus(oMat2);

    ASSERT_EQ(3, oMat1[0].x);
    ASSERT_EQ(5, oMat1[0].y);
    ASSERT_EQ(7, oMat1[0].z);
    ASSERT_EQ(9, oMat1[0].w);
    ASSERT_EQ(11, oMat1[1].x);
    ASSERT_EQ(13, oMat1[1].y);
    ASSERT_EQ(15, oMat1[1].z);
    ASSERT_EQ(17, oMat1[1].w);
    ASSERT_EQ(19, oMat1[2].x);
    ASSERT_EQ(21, oMat1[2].y);
    ASSERT_EQ(23, oMat1[2].z);
    ASSERT_EQ(25, oMat1[2].w);
}

TEST_F(Mat3x4Suite, PlusMatItself) {
    sgf::type::Mat3x4 oMat(
        sgf::type::Vec4(1, 2, 3, 4),
        sgf::type::Vec4(5, 6, 7, 8),
        sgf::type::Vec4(9, 10, 11, 12)
    );

    oMat.plus(oMat);

    ASSERT_EQ(2, oMat[0].x);
    ASSERT_EQ(4, oMat[0].y);
    ASSERT_EQ(6, oMat[0].z);
    ASSERT_EQ(8, oMat[0].w);
    ASSERT_EQ(10, oMat[1].x);
    ASSERT_EQ(12, oMat[1].y);
    ASSERT_EQ(14, oMat[1].z);
    ASSERT_EQ(16, oMat[1].w);
    ASSERT_EQ(18, oMat[2].x);
    ASSERT_EQ(20, oMat[2].y);
    ASSERT_EQ(22, oMat[2].z);
    ASSERT_EQ(24, oMat[2].w);
}

TEST_F(Mat3x4Suite, MinusTwoMat) {
    sgf::type::Mat3x4 oMat1(
        sgf::type::Vec4(1, 2, 3, 4),
        sgf::type::Vec4(5, 6, 7, 8),
        sgf::type::Vec4(9, 10, 11, 12)
    );
    sgf::type::Mat3x4 oMat2(
        sgf::type::Vec4(2, 3, 4, 5),
        sgf::type::Vec4(6, 7, 8, 9),
        sgf::type::Vec4(10, 11, 12, 13)
    );

    oMat1.minus(oMat2);

    ASSERT_EQ(-1, oMat1[0].x);
    ASSERT_EQ(-1, oMat1[0].y);
    ASSERT_EQ(-1, oMat1[0].z);
    ASSERT_EQ(-1, oMat1[0].w);
    ASSERT_EQ(-1, oMat1[1].x);
    ASSERT_EQ(-1, oMat1[1].y);
    ASSERT_EQ(-1, oMat1[1].z);
    ASSERT_EQ(-1, oMat1[1].w);
    ASSERT_EQ(-1, oMat1[2].x);
    ASSERT_EQ(-1, oMat1[2].y);
    ASSERT_EQ(-1, oMat1[2].z);
    ASSERT_EQ(-1, oMat1[2].w);
}

TEST_F(Mat3x4Suite, MinusMatItself) {
    sgf::type::Mat3x4 oMat(
        sgf::type::Vec4(1, 2, 3, 4),
        sgf::type::Vec4(5, 6, 7, 8),
        sgf::type::Vec4(9, 10, 11, 12)
    );

    oMat.minus(oMat);

    ASSERT_EQ(0, oMat[0].x);
    ASSERT_EQ(0, oMat[0].y);
    ASSERT_EQ(0, oMat[0].z);
    ASSERT_EQ(0, oMat[0].w);
    ASSERT_EQ(0, oMat[1].x);
    ASSERT_EQ(0, oMat[1].y);
    ASSERT_EQ(0, oMat[1].z);
    ASSERT_EQ(0, oMat[1].w);
    ASSERT_EQ(0, oMat[2].x);
    ASSERT_EQ(0, oMat[2].y);
    ASSERT_EQ(0, oMat[2].z);
    ASSERT_EQ(0, oMat[2].w);
}

TEST_F(Mat3x4Suite, MultiplyMat) {
    sgf::type::Mat3x4 oMat(
        sgf::type::Vec4(1, 2, 3, 4),
        sgf::type::Vec4(5, 6, 7, 8),
        sgf::type::Vec4(9, 10, 11, 12)
    );

    oMat.multiply(2);

    ASSERT_EQ(2, oMat[0].x);
    ASSERT_EQ(4, oMat[0].y);
    ASSERT_EQ(6, oMat[0].z);
    ASSERT_EQ(8, oMat[0].w);
    ASSERT_EQ(10, oMat[1].x);
    ASSERT_EQ(12, oMat[1].y);
    ASSERT_EQ(14, oMat[1].z);
    ASSERT_EQ(16, oMat[1].w);
    ASSERT_EQ(18, oMat[2].x);
    ASSERT_EQ(20, oMat[2].y);
    ASSERT_EQ(22, oMat[2].z);
    ASSERT_EQ(24, oMat[2].w);
}

TEST_F(Mat3x4Suite, DivideMat) {
    sgf::type::Mat3x4 oMat(
        sgf::type::Vec4(1, 2, 3, 4),
        sgf::type::Vec4(5, 6, 7, 8),
        sgf::type::Vec4(9, 10, 11, 12)
    );

    oMat.divide(1);

    ASSERT_FLOAT_EQ(1.0, oMat[0].x);
}

TEST_F(Mat3x4Suite, TwoEqualItSelf) {
    sgf::type::Mat3x4 oMat(
        sgf::type::Vec4(1, 2, 3, 4),
        sgf::type::Vec4(5, 6, 7, 8),
        sgf::type::Vec4(9, 10, 11, 12)
    );
    ASSERT_TRUE(oMat.equal(oMat));
}

TEST_F(Mat3x4Suite, TwoEqualMat) {
    sgf::type::Mat3x4 oMat1(
        sgf::type::Vec4(1, 2, 3, 4),
        sgf::type::Vec4(5, 6, 7, 8),
        sgf::type::Vec4(9, 10, 11, 12)
    );
    sgf::type::Mat3x4 oMat2(
        sgf::type::Vec4(1, 2, 3, 4),
        sgf::type::Vec4(5, 6, 7, 8),
        sgf::type::Vec4(9, 10, 11, 12)
    );
    ASSERT_TRUE(oMat1.equal(oMat2));
}

TEST_F(Mat3x4Suite, TwoNonEqualMat) {
    sgf::type::Mat3x4 oMat1(
        sgf::type::Vec4(1, 2, 3, 4),
        sgf::type::Vec4(5, 6, 7, 8),
        sgf::type::Vec4(9, 10, 11, 12)
    );
    sgf::type::Mat3x4 oMat2(
        sgf::type::Vec4(2, 3, 4, 5),
        sgf::type::Vec4(6, 7, 8, 9),
        sgf::type::Vec4(10, 11, 12, 13)
    );
    ASSERT_FALSE(oMat1.equal(oMat2));
}

TEST_F(Mat3x4Suite, CastToGLMMat) {
    sgf::type::Mat3x4 oSGFMat(
        sgf::type::Vec4(1, 2, 3, 4),
        sgf::type::Vec4(5, 6, 7, 8),
        sgf::type::Vec4(9, 10, 11, 12)
    );
    glm::mat3x4& rGLMMat = sgf::type::toGLM(oSGFMat);

    ASSERT_EQ(1, rGLMMat[0].x);
}

TEST_F(Mat3x4Suite, CastToGLMMatIsSameAddress) {
    sgf::type::Mat3x4 oSGFMat(
        sgf::type::Vec4(1, 2, 3, 4),
        sgf::type::Vec4(5, 6, 7, 8),
        sgf::type::Vec4(9, 10, 11, 12)
    );
    glm::mat3x4& rGLMMat = sgf::type::toGLM(oSGFMat);

    rGLMMat[0].x = 99;
    ASSERT_EQ(99, oSGFMat[0].x);
}

TEST_F(Mat3x4Suite, CastFromGLMMat) {
    glm::mat3x4 oGLMMat(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
    sgf::type::Mat3x4& rSGFMat = sgf::type::toSGF(oGLMMat);

    ASSERT_EQ(1, rSGFMat[0].x);
}

TEST_F(Mat3x4Suite, CastFromGLMMatIsSameAddress) {
    glm::mat3x4 oGLMMat(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
    sgf::type::Mat3x4& rSGFMat = sgf::type::toSGF(oGLMMat);

    rSGFMat[0].x = 99;
    ASSERT_EQ(99, oGLMMat[0].x);
}
