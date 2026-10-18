#include <gtest/gtest.h>

#include <glm/mat3x3.hpp>

#include "sgf/type/mat3.h"
#include "sgf/type/casting/cast_mat3.h"

class Mat3Suite: public testing::Test {
};

TEST_F(Mat3Suite, CreateEmpty) {
    sgf::type::Mat3 oMat;

    ASSERT_EQ(0, oMat[0].x);
    ASSERT_EQ(0, oMat[0].y);
    ASSERT_EQ(0, oMat[0].z);
    ASSERT_EQ(0, oMat[1].x);
    ASSERT_EQ(0, oMat[1].y);
    ASSERT_EQ(0, oMat[1].z);
    ASSERT_EQ(0, oMat[2].x);
    ASSERT_EQ(0, oMat[2].y);
    ASSERT_EQ(0, oMat[2].z);
}

TEST_F(Mat3Suite, CreateWithScale) {
    sgf::type::Mat3 oMat(2);

    ASSERT_EQ(2, oMat[0].x);
    ASSERT_EQ(0, oMat[0].y);
    ASSERT_EQ(0, oMat[0].z);
    ASSERT_EQ(0, oMat[1].x);
    ASSERT_EQ(2, oMat[1].y);
    ASSERT_EQ(0, oMat[1].z);
    ASSERT_EQ(0, oMat[2].x);
    ASSERT_EQ(0, oMat[2].y);
    ASSERT_EQ(2, oMat[2].z);
}

TEST_F(Mat3Suite, CreateWithColumns) {
    sgf::type::Mat3 oMat(
        sgf::type::Vec3(1, 2, 3),
        sgf::type::Vec3(4, 5, 6),
        sgf::type::Vec3(7, 8, 9)
    );

    ASSERT_EQ(1, oMat[0].x);
    ASSERT_EQ(2, oMat[0].y);
    ASSERT_EQ(3, oMat[0].z);
    ASSERT_EQ(4, oMat[1].x);
    ASSERT_EQ(5, oMat[1].y);
    ASSERT_EQ(6, oMat[1].z);
    ASSERT_EQ(7, oMat[2].x);
    ASSERT_EQ(8, oMat[2].y);
    ASSERT_EQ(9, oMat[2].z);
}

TEST_F(Mat3Suite, CreateWithArray) {
    float arrVal[3][3] = {
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 }
    };
    sgf::type::Mat3 oMat(arrVal);

    ASSERT_EQ(1, oMat[0].x);
    ASSERT_EQ(2, oMat[0].y);
    ASSERT_EQ(3, oMat[0].z);
    ASSERT_EQ(4, oMat[1].x);
    ASSERT_EQ(5, oMat[1].y);
    ASSERT_EQ(6, oMat[1].z);
    ASSERT_EQ(7, oMat[2].x);
    ASSERT_EQ(8, oMat[2].y);
    ASSERT_EQ(9, oMat[2].z);
}

TEST_F(Mat3Suite, BracketGetter) {
    sgf::type::Mat3 oMat(
        sgf::type::Vec3(1, 2, 3),
        sgf::type::Vec3(4, 5, 6),
        sgf::type::Vec3(7, 8, 9)
    );

    ASSERT_EQ(1, oMat[0].x);
    oMat[0].x = 100;
    ASSERT_EQ(100, oMat[0].x);
}

TEST_F(Mat3Suite, ConstBracketGetter) {
    const sgf::type::Mat3 oMat(
        sgf::type::Vec3(1, 2, 3),
        sgf::type::Vec3(4, 5, 6),
        sgf::type::Vec3(7, 8, 9)
    );

    ASSERT_EQ(1, oMat[0].x);
    ASSERT_EQ(9, oMat[2].z);
}

TEST_F(Mat3Suite, PlusTwoMat) {
    sgf::type::Mat3 oMat1(
        sgf::type::Vec3(1, 2, 3),
        sgf::type::Vec3(4, 5, 6),
        sgf::type::Vec3(7, 8, 9)
    );
    sgf::type::Mat3 oMat2(
        sgf::type::Vec3(2, 3, 4),
        sgf::type::Vec3(5, 6, 7),
        sgf::type::Vec3(8, 9, 10)
    );

    oMat1.plus(oMat2);

    ASSERT_EQ(3, oMat1[0].x);
    ASSERT_EQ(5, oMat1[0].y);
    ASSERT_EQ(7, oMat1[0].z);
    ASSERT_EQ(9, oMat1[1].x);
    ASSERT_EQ(11, oMat1[1].y);
    ASSERT_EQ(13, oMat1[1].z);
    ASSERT_EQ(15, oMat1[2].x);
    ASSERT_EQ(17, oMat1[2].y);
    ASSERT_EQ(19, oMat1[2].z);
}

TEST_F(Mat3Suite, PlusMatItself) {
    sgf::type::Mat3 oMat(
        sgf::type::Vec3(1, 2, 3),
        sgf::type::Vec3(4, 5, 6),
        sgf::type::Vec3(7, 8, 9)
    );

    oMat.plus(oMat);

    ASSERT_EQ(2, oMat[0].x);
    ASSERT_EQ(4, oMat[0].y);
    ASSERT_EQ(6, oMat[0].z);
    ASSERT_EQ(8, oMat[1].x);
    ASSERT_EQ(10, oMat[1].y);
    ASSERT_EQ(12, oMat[1].z);
    ASSERT_EQ(14, oMat[2].x);
    ASSERT_EQ(16, oMat[2].y);
    ASSERT_EQ(18, oMat[2].z);
}

TEST_F(Mat3Suite, MinusTwoMat) {
    sgf::type::Mat3 oMat1(
        sgf::type::Vec3(1, 2, 3),
        sgf::type::Vec3(4, 5, 6),
        sgf::type::Vec3(7, 8, 9)
    );
    sgf::type::Mat3 oMat2(
        sgf::type::Vec3(2, 3, 4),
        sgf::type::Vec3(5, 6, 7),
        sgf::type::Vec3(8, 9, 10)
    );

    oMat1.minus(oMat2);

    ASSERT_EQ(-1, oMat1[0].x);
    ASSERT_EQ(-1, oMat1[0].y);
    ASSERT_EQ(-1, oMat1[0].z);
    ASSERT_EQ(-1, oMat1[1].x);
    ASSERT_EQ(-1, oMat1[1].y);
    ASSERT_EQ(-1, oMat1[1].z);
    ASSERT_EQ(-1, oMat1[2].x);
    ASSERT_EQ(-1, oMat1[2].y);
    ASSERT_EQ(-1, oMat1[2].z);
}

TEST_F(Mat3Suite, MinusMatItself) {
    sgf::type::Mat3 oMat(
        sgf::type::Vec3(1, 2, 3),
        sgf::type::Vec3(4, 5, 6),
        sgf::type::Vec3(7, 8, 9)
    );

    oMat.minus(oMat);

    ASSERT_EQ(0, oMat[0].x);
    ASSERT_EQ(0, oMat[0].y);
    ASSERT_EQ(0, oMat[0].z);
    ASSERT_EQ(0, oMat[1].x);
    ASSERT_EQ(0, oMat[1].y);
    ASSERT_EQ(0, oMat[1].z);
    ASSERT_EQ(0, oMat[2].x);
    ASSERT_EQ(0, oMat[2].y);
    ASSERT_EQ(0, oMat[2].z);
}

TEST_F(Mat3Suite, MultiplyMat) {
    sgf::type::Mat3 oMat(
        sgf::type::Vec3(1, 2, 3),
        sgf::type::Vec3(4, 5, 6),
        sgf::type::Vec3(7, 8, 9)
    );

    oMat.multiply(2);

    ASSERT_EQ(2, oMat[0].x);
    ASSERT_EQ(4, oMat[0].y);
    ASSERT_EQ(6, oMat[0].z);
    ASSERT_EQ(8, oMat[1].x);
    ASSERT_EQ(10, oMat[1].y);
    ASSERT_EQ(12, oMat[1].z);
    ASSERT_EQ(14, oMat[2].x);
    ASSERT_EQ(16, oMat[2].y);
    ASSERT_EQ(18, oMat[2].z);
}

TEST_F(Mat3Suite, DivideMat) {
    sgf::type::Mat3 oMat(
        sgf::type::Vec3(1, 2, 3),
        sgf::type::Vec3(4, 5, 6),
        sgf::type::Vec3(7, 8, 9)
    );

    oMat.divide(1);

    ASSERT_FLOAT_EQ(1.0, oMat[0].x);
}

TEST_F(Mat3Suite, TwoEqualItSelf) {
    sgf::type::Mat3 oMat(
        sgf::type::Vec3(1, 2, 3),
        sgf::type::Vec3(4, 5, 6),
        sgf::type::Vec3(7, 8, 9)
    );
    ASSERT_TRUE(oMat.equal(oMat));
}

TEST_F(Mat3Suite, TwoEqualMat) {
    sgf::type::Mat3 oMat1(
        sgf::type::Vec3(1, 2, 3),
        sgf::type::Vec3(4, 5, 6),
        sgf::type::Vec3(7, 8, 9)
    );
    sgf::type::Mat3 oMat2(
        sgf::type::Vec3(1, 2, 3),
        sgf::type::Vec3(4, 5, 6),
        sgf::type::Vec3(7, 8, 9)
    );
    ASSERT_TRUE(oMat1.equal(oMat2));
}

TEST_F(Mat3Suite, TwoNonEqualMat) {
    sgf::type::Mat3 oMat1(
        sgf::type::Vec3(1, 2, 3),
        sgf::type::Vec3(4, 5, 6),
        sgf::type::Vec3(7, 8, 9)
    );
    sgf::type::Mat3 oMat2(
        sgf::type::Vec3(2, 3, 4),
        sgf::type::Vec3(5, 6, 7),
        sgf::type::Vec3(8, 9, 10)
    );
    ASSERT_FALSE(oMat1.equal(oMat2));
}

TEST_F(Mat3Suite, CastToGLMMat) {
    sgf::type::Mat3 oSGFMat(
        sgf::type::Vec3(1, 2, 3),
        sgf::type::Vec3(4, 5, 6),
        sgf::type::Vec3(7, 8, 9)
    );
    glm::mat3& rGLMMat = sgf::type::toGLM(oSGFMat);

    ASSERT_EQ(1, rGLMMat[0].x);
    ASSERT_EQ(9, rGLMMat[2].z);
}

TEST_F(Mat3Suite, CastToGLMMatIsSameAddress) {
    sgf::type::Mat3 oSGFMat(
        sgf::type::Vec3(1, 2, 3),
        sgf::type::Vec3(4, 5, 6),
        sgf::type::Vec3(7, 8, 9)
    );
    glm::mat3& rGLMMat = sgf::type::toGLM(oSGFMat);

    rGLMMat[0].x = 99;
    ASSERT_EQ(99, oSGFMat[0].x);
}

TEST_F(Mat3Suite, CastFromGLMMat) {
    glm::mat3 oGLMMat(1, 2, 3, 4, 5, 6, 7, 8, 9);
    sgf::type::Mat3& rSGFMat = sgf::type::toSGF(oGLMMat);

    ASSERT_EQ(1, rSGFMat[0].x);
    ASSERT_EQ(9, rSGFMat[2].z);
}

TEST_F(Mat3Suite, CastFromGLMMatIsSameAddress) {
    glm::mat3 oGLMMat(1, 2, 3, 4, 5, 6, 7, 8, 9);
    sgf::type::Mat3& rSGFMat = sgf::type::toSGF(oGLMMat);

    rSGFMat[0].x = 99;
    ASSERT_EQ(99, oGLMMat[0].x);
}
