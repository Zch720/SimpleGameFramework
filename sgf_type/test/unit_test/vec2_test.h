#include <gtest/gtest.h>

#include <glm/vec2.hpp>

#include "sgf/type/vec2.h"
#include "sgf/type/casting/cast_vec2.h"

class Vec2Suite: public testing::Test {
};

TEST_F(Vec2Suite, CreateEmpty) {
    sgf::type::Vec2 oVec;

    ASSERT_EQ(0, oVec.x);
    ASSERT_EQ(0, oVec.y);
}

TEST_F(Vec2Suite, CreateWithScale) {
    sgf::type::Vec2 oVec(2);

    ASSERT_EQ(2, oVec.x);
    ASSERT_EQ(2, oVec.y);
}

TEST_F(Vec2Suite, CreateWithXY) {
    sgf::type::Vec2 oVec(4, 7);

    ASSERT_EQ(4, oVec.x);
    ASSERT_EQ(7, oVec.y);
}

TEST_F(Vec2Suite, CreateWithArray) {
    float arrVal[2] = { 1, 2 };
    sgf::type::Vec2 oVec(arrVal);

    ASSERT_EQ(1, oVec.x);
    ASSERT_EQ(2, oVec.y);
}

TEST_F(Vec2Suite, BracketGetter) {
    sgf::type::Vec2 oVec(2, 3);

    ASSERT_EQ(2, oVec[0]);
    ASSERT_EQ(3, oVec[1]);

    oVec[0] = 5;
    oVec[1] = 7;
    
    ASSERT_EQ(5, oVec[0]);
    ASSERT_EQ(7, oVec[1]);
}

TEST_F(Vec2Suite, ConstBracketGetter) {
    const sgf::type::Vec2 oVec(2, 3);

    ASSERT_EQ(2, oVec[0]);
    ASSERT_EQ(3, oVec[1]);
}

TEST_F(Vec2Suite, PlusTwoVec) {
    sgf::type::Vec2 oVec1(1, 2);
    sgf::type::Vec2 oVec2(3, 4);

    oVec1.plus(oVec2);
    
    ASSERT_EQ(4, oVec1.x);
    ASSERT_EQ(6, oVec1.y);
    ASSERT_EQ(3, oVec2.x);
    ASSERT_EQ(4, oVec2.y);
}

TEST_F(Vec2Suite, PlusVecItself) {
    sgf::type::Vec2 oVec(1, 2);

    oVec.plus(oVec);
    
    ASSERT_EQ(2, oVec.x);
    ASSERT_EQ(4, oVec.y);
}

TEST_F(Vec2Suite, MinusTwoVec) {
    sgf::type::Vec2 oVec1(1, 2);
    sgf::type::Vec2 oVec2(3, 4);

    oVec1.minus(oVec2);
    
    ASSERT_EQ(-2, oVec1.x);
    ASSERT_EQ(-2, oVec1.y);
    ASSERT_EQ(3, oVec2.x);
    ASSERT_EQ(4, oVec2.y);
}

TEST_F(Vec2Suite, MinusVecItself) {
    sgf::type::Vec2 oVec(1, 2);

    oVec.minus(oVec);
    
    ASSERT_EQ(0, oVec.x);
    ASSERT_EQ(0, oVec.y);
}

TEST_F(Vec2Suite, MultiplyVec) {
    sgf::type::Vec2 oVec(1, 2);

    oVec.multiply(5);

    ASSERT_EQ(5, oVec.x);
    ASSERT_EQ(10, oVec.y);
}

TEST_F(Vec2Suite, DivideVec) {
    sgf::type::Vec2 oVec(1, 2);

    oVec.divide(5);

    ASSERT_FLOAT_EQ(0.2f, oVec.x);
    ASSERT_FLOAT_EQ(0.4f, oVec.y);
}

TEST_F(Vec2Suite, TwoEqualItSelf) {
    sgf::type::Vec2 oVec(2, 3);

    ASSERT_TRUE(oVec.equal(oVec));
}

TEST_F(Vec2Suite, TwoEqualVec) {
    sgf::type::Vec2 oVec1(2, 3);
    sgf::type::Vec2 oVec2(2, 3);
    
    ASSERT_TRUE(oVec1.equal(oVec2));
}

TEST_F(Vec2Suite, TwoNonEqualVec) {
    sgf::type::Vec2 oVec1(2, 3);
    sgf::type::Vec2 oVec2(2, 4);
    
    ASSERT_FALSE(oVec1.equal(oVec2));
}

TEST_F(Vec2Suite, CastToGLMVec) {
    sgf::type::Vec2 oSGFVec(1, 2);
    glm::vec2& rGLMVec = sgf::type::toGLM(oSGFVec);

    ASSERT_EQ(1, rGLMVec.x);
    ASSERT_EQ(2, rGLMVec.y);
}

TEST_F(Vec2Suite, CastToGLMVecIsSameAddress) {
    sgf::type::Vec2 oSGFVec(1, 2);
    glm::vec2& rGLMVec = sgf::type::toGLM(oSGFVec);

    rGLMVec.x = 3;
    rGLMVec.y = 4;

    ASSERT_EQ(3, oSGFVec.x);
    ASSERT_EQ(4, oSGFVec.y);
}

TEST_F(Vec2Suite, CastFromGLMVec) {
    glm::vec2 oGLMVec(1, 2);
    sgf::type::Vec2& rSGFVec = sgf::type::toSGF(oGLMVec);

    ASSERT_EQ(1, rSGFVec.x);
    ASSERT_EQ(2, rSGFVec.y);
}

TEST_F(Vec2Suite, CastFromGLMVecIsSameAddress) {
    glm::vec2 oGLMVec(1, 2);
    sgf::type::Vec2& rSGFVec = sgf::type::toSGF(oGLMVec);

    rSGFVec.x = 3;
    rSGFVec.y = 4;
    
    ASSERT_EQ(3, oGLMVec.x);
    ASSERT_EQ(4, oGLMVec.y);
}
