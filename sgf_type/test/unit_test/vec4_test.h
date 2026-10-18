#include <gtest/gtest.h>

#include <glm/vec4.hpp>

#include "sgf/type/vec4.h"
#include "sgf/type/casting/cast_vec4.h"

class Vec4Suite: public testing::Test {
};

TEST_F(Vec4Suite, CreateEmpty) {
    sgf::type::Vec4 oVec;

    ASSERT_EQ(0, oVec.x);
    ASSERT_EQ(0, oVec.y);
    ASSERT_EQ(0, oVec.z);
    ASSERT_EQ(0, oVec.w);
}

TEST_F(Vec4Suite, CreateWithScale) {
    sgf::type::Vec4 oVec(2);

    ASSERT_EQ(2, oVec.x);
    ASSERT_EQ(2, oVec.y);
    ASSERT_EQ(2, oVec.z);
    ASSERT_EQ(2, oVec.w);
}

TEST_F(Vec4Suite, CreateWithXYZW) {
    sgf::type::Vec4 oVec(4, 7, 3, 9);

    ASSERT_EQ(4, oVec.x);
    ASSERT_EQ(7, oVec.y);
    ASSERT_EQ(3, oVec.z);
    ASSERT_EQ(9, oVec.w);
}

TEST_F(Vec4Suite, CreateWithArray) {
    float arrVal[4] = { 1, 2, 3, 4 };
    sgf::type::Vec4 oVec(arrVal);

    ASSERT_EQ(1, oVec.x);
    ASSERT_EQ(2, oVec.y);
    ASSERT_EQ(3, oVec.z);
    ASSERT_EQ(4, oVec.w);
}

TEST_F(Vec4Suite, BracketGetter) {
    sgf::type::Vec4 oVec(2, 3, 4, 5);

    ASSERT_EQ(2, oVec[0]);
    ASSERT_EQ(3, oVec[1]);
    ASSERT_EQ(4, oVec[2]);
    ASSERT_EQ(5, oVec[3]);

    oVec[0] = 5;
    oVec[1] = 7;
    oVec[2] = 9;
    oVec[3] = 11;
    
    ASSERT_EQ(5, oVec[0]);
    ASSERT_EQ(7, oVec[1]);
    ASSERT_EQ(9, oVec[2]);
    ASSERT_EQ(11, oVec[3]);
}

TEST_F(Vec4Suite, ConstBracketGetter) {
    const sgf::type::Vec4 oVec(2, 3, 4, 5);

    ASSERT_EQ(2, oVec[0]);
    ASSERT_EQ(3, oVec[1]);
    ASSERT_EQ(4, oVec[2]);
    ASSERT_EQ(5, oVec[3]);
}

TEST_F(Vec4Suite, PlusTwoVec) {
    sgf::type::Vec4 oVec1(1, 2, 3, 4);
    sgf::type::Vec4 oVec2(3, 4, 5, 6);

    oVec1.plus(oVec2);
    
    ASSERT_EQ(4, oVec1.x);
    ASSERT_EQ(6, oVec1.y);
    ASSERT_EQ(8, oVec1.z);
    ASSERT_EQ(10, oVec1.w);
    ASSERT_EQ(3, oVec2.x);
    ASSERT_EQ(4, oVec2.y);
    ASSERT_EQ(5, oVec2.z);
    ASSERT_EQ(6, oVec2.w);
}

TEST_F(Vec4Suite, PlusVecItself) {
    sgf::type::Vec4 oVec(1, 2, 3, 4);

    oVec.plus(oVec);
    
    ASSERT_EQ(2, oVec.x);
    ASSERT_EQ(4, oVec.y);
    ASSERT_EQ(6, oVec.z);
    ASSERT_EQ(8, oVec.w);
}

TEST_F(Vec4Suite, MinusTwoVec) {
    sgf::type::Vec4 oVec1(1, 2, 3, 4);
    sgf::type::Vec4 oVec2(3, 4, 5, 6);

    oVec1.minus(oVec2);
    
    ASSERT_EQ(-2, oVec1.x);
    ASSERT_EQ(-2, oVec1.y);
    ASSERT_EQ(-2, oVec1.z);
    ASSERT_EQ(-2, oVec1.w);
    ASSERT_EQ(3, oVec2.x);
    ASSERT_EQ(4, oVec2.y);
    ASSERT_EQ(5, oVec2.z);
    ASSERT_EQ(6, oVec2.w);
}

TEST_F(Vec4Suite, MinusVecItself) {
    sgf::type::Vec4 oVec(1, 2, 3, 4);

    oVec.minus(oVec);
    
    ASSERT_EQ(0, oVec.x);
    ASSERT_EQ(0, oVec.y);
    ASSERT_EQ(0, oVec.z);
    ASSERT_EQ(0, oVec.w);
}

TEST_F(Vec4Suite, MultiplyVec) {
    sgf::type::Vec4 oVec(1, 2, 3, 4);

    oVec.multiply(5);

    ASSERT_EQ(5, oVec.x);
    ASSERT_EQ(10, oVec.y);
    ASSERT_EQ(15, oVec.z);
    ASSERT_EQ(20, oVec.w);
}

TEST_F(Vec4Suite, DivideVec) {
    sgf::type::Vec4 oVec(1, 2, 3, 4);

    oVec.divide(5);

    ASSERT_FLOAT_EQ(0.2f, oVec.x);
    ASSERT_FLOAT_EQ(0.4f, oVec.y);
    ASSERT_FLOAT_EQ(0.6f, oVec.z);
    ASSERT_FLOAT_EQ(0.8f, oVec.w);
}

TEST_F(Vec4Suite, TwoEqualItSelf) {
    sgf::type::Vec4 oVec(2, 3, 4, 5);

    ASSERT_TRUE(oVec.equal(oVec));
}

TEST_F(Vec4Suite, TwoEqualVec) {
    sgf::type::Vec4 oVec1(2, 3, 4, 5);
    sgf::type::Vec4 oVec2(2, 3, 4, 5);
    
    ASSERT_TRUE(oVec1.equal(oVec2));
}

TEST_F(Vec4Suite, TwoNonEqualVec) {
    sgf::type::Vec4 oVec1(2, 3, 4, 5);
    sgf::type::Vec4 oVec2(2, 4, 6, 8);
    
    ASSERT_FALSE(oVec1.equal(oVec2));
}

TEST_F(Vec4Suite, CastToGLMVec) {
    sgf::type::Vec4 oSGFVec(1, 2, 3, 4);
    glm::vec4& rGLMVec = sgf::type::toGLM(oSGFVec);

    ASSERT_EQ(1, rGLMVec.x);
    ASSERT_EQ(2, rGLMVec.y);
    ASSERT_EQ(3, rGLMVec.z);
    ASSERT_EQ(4, rGLMVec.w);
}

TEST_F(Vec4Suite, CastToGLMVecIsSameAddress) {
    sgf::type::Vec4 oSGFVec(1, 2, 3, 4);
    glm::vec4& rGLMVec = sgf::type::toGLM(oSGFVec);

    rGLMVec.x = 3;
    rGLMVec.y = 4;
    rGLMVec.z = 5;
    rGLMVec.w = 6;
    
    ASSERT_EQ(3, oSGFVec.x);
    ASSERT_EQ(4, oSGFVec.y);
    ASSERT_EQ(5, oSGFVec.z);
    ASSERT_EQ(6, oSGFVec.w);
}

TEST_F(Vec4Suite, CastFromGLMVec) {
    glm::vec4 oGLMVec(1, 2, 3, 4);
    sgf::type::Vec4& rSGFVec = sgf::type::toSGF(oGLMVec);

    ASSERT_EQ(1, rSGFVec.x);
    ASSERT_EQ(2, rSGFVec.y);
    ASSERT_EQ(3, rSGFVec.z);
    ASSERT_EQ(4, rSGFVec.w);
}

TEST_F(Vec4Suite, CastFromGLMVecIsSameAddress) {
    glm::vec4 oGLMVec(1, 2, 3, 4);
    sgf::type::Vec4& rSGFVec = sgf::type::toSGF(oGLMVec);

    rSGFVec.x = 3;
    rSGFVec.y = 4;
    rSGFVec.z = 5;
    rSGFVec.w = 6;
    
    ASSERT_EQ(3, oGLMVec.x);
    ASSERT_EQ(4, oGLMVec.y);
    ASSERT_EQ(5, oGLMVec.z);
    ASSERT_EQ(6, oGLMVec.w);
}
