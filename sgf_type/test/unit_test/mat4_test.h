#include <gtest/gtest.h>

#include <glm/mat4x4.hpp>

#include "sgf/type/mat4.h"
#include "sgf/type/casting/cast_mat4.h"

class Mat4Suite: public testing::Test {
};

TEST_F(Mat4Suite, CreateEmpty) {
    sgf::type::Mat4 oMat;

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
    ASSERT_EQ(0, oMat[3].x);
    ASSERT_EQ(0, oMat[3].y);
    ASSERT_EQ(0, oMat[3].z);
    ASSERT_EQ(0, oMat[3].w);
}

TEST_F(Mat4Suite, CreateWithScale) {
    sgf::type::Mat4 oMat(2);

    ASSERT_EQ(2, oMat[0].x);
    ASSERT_EQ(0, oMat[0].y);
    ASSERT_EQ(0, oMat[0].z);
    ASSERT_EQ(0, oMat[0].w);
    ASSERT_EQ(0, oMat[1].x);
    ASSERT_EQ(2, oMat[1].y);
    ASSERT_EQ(0, oMat[1].z);
    ASSERT_EQ(0, oMat[1].w);
    ASSERT_EQ(0, oMat[2].x);
    ASSERT_EQ(0, oMat[2].y);
    ASSERT_EQ(2, oMat[2].z);
    ASSERT_EQ(0, oMat[2].w);
    ASSERT_EQ(0, oMat[3].x);
    ASSERT_EQ(0, oMat[3].y);
    ASSERT_EQ(0, oMat[3].z);
    ASSERT_EQ(2, oMat[3].w);
}

TEST_F(Mat4Suite, CreateWithColumns) {
    sgf::type::Mat4 oMat(
        sgf::type::Vec4(1, 2, 3, 4),
        sgf::type::Vec4(5, 6, 7, 8),
        sgf::type::Vec4(9, 10, 11, 12),
        sgf::type::Vec4(13, 14, 15, 16)
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
    ASSERT_EQ(13, oMat[3].x);
    ASSERT_EQ(14, oMat[3].y);
    ASSERT_EQ(15, oMat[3].z);
    ASSERT_EQ(16, oMat[3].w);
}

TEST_F(Mat4Suite, CreateWithArray) {
    float arrVal[4][4] = {
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 },
        { 13, 14, 15, 16 }
    };
    sgf::type::Mat4 oMat(arrVal);

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
    ASSERT_EQ(13, oMat[3].x);
    ASSERT_EQ(14, oMat[3].y);
    ASSERT_EQ(15, oMat[3].z);
    ASSERT_EQ(16, oMat[3].w);
}

TEST_F(Mat4Suite, BracketGetter) {
    sgf::type::Mat4 oMat(
        sgf::type::Vec4(1, 2, 3, 4),
        sgf::type::Vec4(5, 6, 7, 8),
        sgf::type::Vec4(9, 10, 11, 12),
        sgf::type::Vec4(13, 14, 15, 16)
    );

    ASSERT_EQ(1, oMat[0].x);
    oMat[0].x = 100;
    ASSERT_EQ(100, oMat[0].x);
}

TEST_F(Mat4Suite, ConstBracketGetter) {
    const sgf::type::Mat4 oMat(
        sgf::type::Vec4(1, 2, 3, 4),
        sgf::type::Vec4(5, 6, 7, 8),
        sgf::type::Vec4(9, 10, 11, 12),
        sgf::type::Vec4(13, 14, 15, 16)
    );

    ASSERT_EQ(1, oMat[0].x);
    ASSERT_EQ(16, oMat[3].w);
}

TEST_F(Mat4Suite, PlusTwoMat) {
    sgf::type::Mat4 oMat1(
        sgf::type::Vec4(1, 2, 3, 4),
        sgf::type::Vec4(5, 6, 7, 8),
        sgf::type::Vec4(9, 10, 11, 12),
        sgf::type::Vec4(13, 14, 15, 16)
    );
    sgf::type::Mat4 oMat2(
        sgf::type::Vec4(2, 3, 4, 5),
        sgf::type::Vec4(6, 7, 8, 9),
        sgf::type::Vec4(10, 11, 12, 13),
        sgf::type::Vec4(14, 15, 16, 17)
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
    ASSERT_EQ(27, oMat1[3].x);
    ASSERT_EQ(29, oMat1[3].y);
    ASSERT_EQ(31, oMat1[3].z);
    ASSERT_EQ(33, oMat1[3].w);
}

TEST_F(Mat4Suite, PlusMatItself) {
    sgf::type::Mat4 oMat(
        sgf::type::Vec4(1, 2, 3, 4),
        sgf::type::Vec4(5, 6, 7, 8),
        sgf::type::Vec4(9, 10, 11, 12),
        sgf::type::Vec4(13, 14, 15, 16)
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
    ASSERT_EQ(26, oMat[3].x);
    ASSERT_EQ(28, oMat[3].y);
    ASSERT_EQ(30, oMat[3].z);
    ASSERT_EQ(32, oMat[3].w);
}

TEST_F(Mat4Suite, MinusTwoMat) {
    sgf::type::Mat4 oMat1(
        sgf::type::Vec4(1, 2, 3, 4),
        sgf::type::Vec4(5, 6, 7, 8),
        sgf::type::Vec4(9, 10, 11, 12),
        sgf::type::Vec4(13, 14, 15, 16)
    );
    sgf::type::Mat4 oMat2(
        sgf::type::Vec4(2, 3, 4, 5),
        sgf::type::Vec4(6, 7, 8, 9),
        sgf::type::Vec4(10, 11, 12, 13),
        sgf::type::Vec4(14, 15, 16, 17)
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
    ASSERT_EQ(-1, oMat1[3].x);
    ASSERT_EQ(-1, oMat1[3].y);
    ASSERT_EQ(-1, oMat1[3].z);
    ASSERT_EQ(-1, oMat1[3].w);
}

TEST_F(Mat4Suite, MinusMatItself) {
    sgf::type::Mat4 oMat(
        sgf::type::Vec4(1, 2, 3, 4),
        sgf::type::Vec4(5, 6, 7, 8),
        sgf::type::Vec4(9, 10, 11, 12),
        sgf::type::Vec4(13, 14, 15, 16)
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
    ASSERT_EQ(0, oMat[3].x);
    ASSERT_EQ(0, oMat[3].y);
    ASSERT_EQ(0, oMat[3].z);
    ASSERT_EQ(0, oMat[3].w);
}

TEST_F(Mat4Suite, MultiplyMat) {
    sgf::type::Mat4 oMat(
        sgf::type::Vec4(1, 2, 3, 4),
        sgf::type::Vec4(5, 6, 7, 8),
        sgf::type::Vec4(9, 10, 11, 12),
        sgf::type::Vec4(13, 14, 15, 16)
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
    ASSERT_EQ(26, oMat[3].x);
    ASSERT_EQ(28, oMat[3].y);
    ASSERT_EQ(30, oMat[3].z);
    ASSERT_EQ(32, oMat[3].w);
}

TEST_F(Mat4Suite, DivideMat) {
    sgf::type::Mat4 oMat(
        sgf::type::Vec4(1, 2, 3, 4),
        sgf::type::Vec4(5, 6, 7, 8),
        sgf::type::Vec4(9, 10, 11, 12),
        sgf::type::Vec4(13, 14, 15, 16)
    );

    oMat.divide(1);

    ASSERT_FLOAT_EQ(1.0, oMat[0].x);
}

TEST_F(Mat4Suite, TwoEqualItSelf) {
    sgf::type::Mat4 oMat(
        sgf::type::Vec4(1, 2, 3, 4),
        sgf::type::Vec4(5, 6, 7, 8),
        sgf::type::Vec4(9, 10, 11, 12),
        sgf::type::Vec4(13, 14, 15, 16)
    );
    ASSERT_TRUE(oMat.equal(oMat));
}

TEST_F(Mat4Suite, TwoEqualMat) {
    sgf::type::Mat4 oMat1(
        sgf::type::Vec4(1, 2, 3, 4),
        sgf::type::Vec4(5, 6, 7, 8),
        sgf::type::Vec4(9, 10, 11, 12),
        sgf::type::Vec4(13, 14, 15, 16)
    );
    sgf::type::Mat4 oMat2(
        sgf::type::Vec4(1, 2, 3, 4),
        sgf::type::Vec4(5, 6, 7, 8),
        sgf::type::Vec4(9, 10, 11, 12),
        sgf::type::Vec4(13, 14, 15, 16)
    );
    ASSERT_TRUE(oMat1.equal(oMat2));
}

TEST_F(Mat4Suite, TwoNonEqualMat) {
    sgf::type::Mat4 oMat1(
        sgf::type::Vec4(1, 2, 3, 4),
        sgf::type::Vec4(5, 6, 7, 8),
        sgf::type::Vec4(9, 10, 11, 12),
        sgf::type::Vec4(13, 14, 15, 16)
    );
    sgf::type::Mat4 oMat2(
        sgf::type::Vec4(2, 3, 4, 5),
        sgf::type::Vec4(6, 7, 8, 9),
        sgf::type::Vec4(10, 11, 12, 13),
        sgf::type::Vec4(14, 15, 16, 17)
    );
    ASSERT_FALSE(oMat1.equal(oMat2));
}

TEST_F(Mat4Suite, CastToGLMMat) {
    sgf::type::Mat4 oSGFMat(
        sgf::type::Vec4(1, 2, 3, 4),
        sgf::type::Vec4(5, 6, 7, 8),
        sgf::type::Vec4(9, 10, 11, 12),
        sgf::type::Vec4(13, 14, 15, 16)
    );
    glm::mat4& rGLMMat = sgf::type::toGLM(oSGFMat);

    ASSERT_EQ(1, rGLMMat[0].x);
    ASSERT_EQ(16, rGLMMat[3].w);
}

TEST_F(Mat4Suite, CastToGLMMatIsSameAddress) {
    sgf::type::Mat4 oSGFMat(
        sgf::type::Vec4(1, 2, 3, 4),
        sgf::type::Vec4(5, 6, 7, 8),
        sgf::type::Vec4(9, 10, 11, 12),
        sgf::type::Vec4(13, 14, 15, 16)
    );
    glm::mat4& rGLMMat = sgf::type::toGLM(oSGFMat);

    rGLMMat[0].x = 99;
    ASSERT_EQ(99, oSGFMat[0].x);
}

TEST_F(Mat4Suite, CastFromGLMMat) {
    glm::mat4 oGLMMat(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    sgf::type::Mat4& rSGFMat = sgf::type::toSGF(oGLMMat);

    ASSERT_EQ(1, rSGFMat[0].x);
    ASSERT_EQ(16, rSGFMat[3].w);
}

TEST_F(Mat4Suite, CastFromGLMMatIsSameAddress) {
    glm::mat4 oGLMMat(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    sgf::type::Mat4& rSGFMat = sgf::type::toSGF(oGLMMat);

    rSGFMat[0].x = 99;
    ASSERT_EQ(99, oGLMMat[0].x);
}
