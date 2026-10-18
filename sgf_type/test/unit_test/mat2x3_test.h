#include <gtest/gtest.h>

#include <glm/mat2x3.hpp>

#include "sgf/type/mat2x3.h"
#include "sgf/type/casting/cast_mat2x3.h"

class Mat2x3Suite: public testing::Test {
};

TEST_F(Mat2x3Suite, CreateEmpty) {
    sgf::type::Mat2x3 oMat;

    ASSERT_EQ(0, oMat[0].x);
    ASSERT_EQ(0, oMat[0].y);
    ASSERT_EQ(0, oMat[0].z);
    ASSERT_EQ(0, oMat[1].x);
    ASSERT_EQ(0, oMat[1].y);
    ASSERT_EQ(0, oMat[1].z);
}

TEST_F(Mat2x3Suite, CreateWithColumns) {
    sgf::type::Mat2x3 oMat(
        sgf::type::Vec3(1, 2, 3),
        sgf::type::Vec3(4, 5, 6)
    );

    ASSERT_EQ(1, oMat[0].x);
    ASSERT_EQ(2, oMat[0].y);
    ASSERT_EQ(3, oMat[0].z);
    ASSERT_EQ(4, oMat[1].x);
    ASSERT_EQ(5, oMat[1].y);
    ASSERT_EQ(6, oMat[1].z);
}

TEST_F(Mat2x3Suite, CreateWithArray) {
    float arrVal[2][3] = {
        { 1, 2, 3 },
        { 4, 5, 6 }
    };
    sgf::type::Mat2x3 oMat(arrVal);

    ASSERT_EQ(1, oMat[0].x);
    ASSERT_EQ(2, oMat[0].y);
    ASSERT_EQ(3, oMat[0].z);
    ASSERT_EQ(4, oMat[1].x);
    ASSERT_EQ(5, oMat[1].y);
    ASSERT_EQ(6, oMat[1].z);
}

TEST_F(Mat2x3Suite, BracketGetter) {
    sgf::type::Mat2x3 oMat(
        sgf::type::Vec3(1, 2, 3),
        sgf::type::Vec3(4, 5, 6)
    );

    ASSERT_EQ(1, oMat[0].x);
    oMat[0].x = 100;
    ASSERT_EQ(100, oMat[0].x);
}

TEST_F(Mat2x3Suite, ConstBracketGetter) {
    const sgf::type::Mat2x3 oMat(
        sgf::type::Vec3(1, 2, 3),
        sgf::type::Vec3(4, 5, 6)
    );

    ASSERT_EQ(1, oMat[0].x);
}

TEST_F(Mat2x3Suite, PlusTwoMat) {
    sgf::type::Mat2x3 oMat1(
        sgf::type::Vec3(1, 2, 3),
        sgf::type::Vec3(4, 5, 6)
    );
    sgf::type::Mat2x3 oMat2(
        sgf::type::Vec3(2, 3, 4),
        sgf::type::Vec3(5, 6, 7)
    );

    oMat1.plus(oMat2);

    ASSERT_EQ(3, oMat1[0].x);
    ASSERT_EQ(5, oMat1[0].y);
    ASSERT_EQ(7, oMat1[0].z);
    ASSERT_EQ(9, oMat1[1].x);
    ASSERT_EQ(11, oMat1[1].y);
    ASSERT_EQ(13, oMat1[1].z);
}

TEST_F(Mat2x3Suite, PlusMatItself) {
    sgf::type::Mat2x3 oMat(
        sgf::type::Vec3(1, 2, 3),
        sgf::type::Vec3(4, 5, 6)
    );

    oMat.plus(oMat);

    ASSERT_EQ(2, oMat[0].x);
    ASSERT_EQ(4, oMat[0].y);
    ASSERT_EQ(6, oMat[0].z);
    ASSERT_EQ(8, oMat[1].x);
    ASSERT_EQ(10, oMat[1].y);
    ASSERT_EQ(12, oMat[1].z);
}

TEST_F(Mat2x3Suite, MinusTwoMat) {
    sgf::type::Mat2x3 oMat1(
        sgf::type::Vec3(1, 2, 3),
        sgf::type::Vec3(4, 5, 6)
    );
    sgf::type::Mat2x3 oMat2(
        sgf::type::Vec3(2, 3, 4),
        sgf::type::Vec3(5, 6, 7)
    );

    oMat1.minus(oMat2);

    ASSERT_EQ(-1, oMat1[0].x);
    ASSERT_EQ(-1, oMat1[0].y);
    ASSERT_EQ(-1, oMat1[0].z);
    ASSERT_EQ(-1, oMat1[1].x);
    ASSERT_EQ(-1, oMat1[1].y);
    ASSERT_EQ(-1, oMat1[1].z);
}

TEST_F(Mat2x3Suite, MinusMatItself) {
    sgf::type::Mat2x3 oMat(
        sgf::type::Vec3(1, 2, 3),
        sgf::type::Vec3(4, 5, 6)
    );

    oMat.minus(oMat);

    ASSERT_EQ(0, oMat[0].x);
    ASSERT_EQ(0, oMat[0].y);
    ASSERT_EQ(0, oMat[0].z);
    ASSERT_EQ(0, oMat[1].x);
    ASSERT_EQ(0, oMat[1].y);
    ASSERT_EQ(0, oMat[1].z);
}

TEST_F(Mat2x3Suite, MultiplyMat) {
    sgf::type::Mat2x3 oMat(
        sgf::type::Vec3(1, 2, 3),
        sgf::type::Vec3(4, 5, 6)
    );

    oMat.multiply(2);

    ASSERT_EQ(2, oMat[0].x);
    ASSERT_EQ(4, oMat[0].y);
    ASSERT_EQ(6, oMat[0].z);
    ASSERT_EQ(8, oMat[1].x);
    ASSERT_EQ(10, oMat[1].y);
    ASSERT_EQ(12, oMat[1].z);
}

TEST_F(Mat2x3Suite, DivideMat) {
    sgf::type::Mat2x3 oMat(
        sgf::type::Vec3(1, 2, 3),
        sgf::type::Vec3(4, 5, 6)
    );

    oMat.divide(1);

    ASSERT_FLOAT_EQ(1.0, oMat[0].x);
}

TEST_F(Mat2x3Suite, TwoEqualItSelf) {
    sgf::type::Mat2x3 oMat(
        sgf::type::Vec3(1, 2, 3),
        sgf::type::Vec3(4, 5, 6)
    );
    ASSERT_TRUE(oMat.equal(oMat));
}

TEST_F(Mat2x3Suite, TwoEqualMat) {
    sgf::type::Mat2x3 oMat1(
        sgf::type::Vec3(1, 2, 3),
        sgf::type::Vec3(4, 5, 6)
    );
    sgf::type::Mat2x3 oMat2(
        sgf::type::Vec3(1, 2, 3),
        sgf::type::Vec3(4, 5, 6)
    );
    ASSERT_TRUE(oMat1.equal(oMat2));
}

TEST_F(Mat2x3Suite, TwoNonEqualMat) {
    sgf::type::Mat2x3 oMat1(
        sgf::type::Vec3(1, 2, 3),
        sgf::type::Vec3(4, 5, 6)
    );
    sgf::type::Mat2x3 oMat2(
        sgf::type::Vec3(2, 3, 4),
        sgf::type::Vec3(5, 6, 7)
    );
    ASSERT_FALSE(oMat1.equal(oMat2));
}

TEST_F(Mat2x3Suite, CastToGLMMat) {
    sgf::type::Mat2x3 oSGFMat(
        sgf::type::Vec3(1, 2, 3),
        sgf::type::Vec3(4, 5, 6)
    );
    glm::mat2x3& rGLMMat = sgf::type::toGLM(oSGFMat);

    ASSERT_EQ(1, rGLMMat[0].x);
}

TEST_F(Mat2x3Suite, CastToGLMMatIsSameAddress) {
    sgf::type::Mat2x3 oSGFMat(
        sgf::type::Vec3(1, 2, 3),
        sgf::type::Vec3(4, 5, 6)
    );
    glm::mat2x3& rGLMMat = sgf::type::toGLM(oSGFMat);

    rGLMMat[0].x = 99;
    ASSERT_EQ(99, oSGFMat[0].x);
}

TEST_F(Mat2x3Suite, CastFromGLMMat) {
    glm::mat2x3 oGLMMat(1, 2, 3, 4, 5, 6);
    sgf::type::Mat2x3& rSGFMat = sgf::type::toSGF(oGLMMat);

    ASSERT_EQ(1, rSGFMat[0].x);
}

TEST_F(Mat2x3Suite, CastFromGLMMatIsSameAddress) {
    glm::mat2x3 oGLMMat(1, 2, 3, 4, 5, 6);
    sgf::type::Mat2x3& rSGFMat = sgf::type::toSGF(oGLMMat);

    rSGFMat[0].x = 99;
    ASSERT_EQ(99, oGLMMat[0].x);
}
