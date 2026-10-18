#include <gtest/gtest.h>

#include <glm/vec3.hpp>

#include "sgf/type/vec3.h"
#include "sgf/type/casting/cast_vec3.h"

class Vec3Suite: public testing::Test {
};

TEST_F(Vec3Suite, CreateEmpty) {
    sgf::type::Vec3 oVec;

    ASSERT_EQ(0, oVec.x);
    ASSERT_EQ(0, oVec.y);
    ASSERT_EQ(0, oVec.z);
}

TEST_F(Vec3Suite, CreateWithScale) {
    sgf::type::Vec3 oVec(2);

    ASSERT_EQ(2, oVec.x);
    ASSERT_EQ(2, oVec.y);
    ASSERT_EQ(2, oVec.z);
}

TEST_F(Vec3Suite, CreateWithXY) {
    sgf::type::Vec3 oVec(4, 7, 3);

    ASSERT_EQ(4, oVec.x);
    ASSERT_EQ(7, oVec.y);
    ASSERT_EQ(3, oVec.z);
}

TEST_F(Vec3Suite, CreateWithArray) {
    float arrVal[3] = { 1, 2, 3 };
    sgf::type::Vec3 oVec(arrVal);

    ASSERT_EQ(1, oVec.x);
    ASSERT_EQ(2, oVec.y);
    ASSERT_EQ(3, oVec.z);
}

TEST_F(Vec3Suite, BracketGetter) {
    sgf::type::Vec3 oVec(2, 3, 4);

    ASSERT_EQ(2, oVec[0]);
    ASSERT_EQ(3, oVec[1]);
    ASSERT_EQ(4, oVec[2]);

    oVec[0] = 5;
    oVec[1] = 7;
    oVec[2] = 9;
    
    ASSERT_EQ(5, oVec[0]);
    ASSERT_EQ(7, oVec[1]);
    ASSERT_EQ(9, oVec[2]);
}

TEST_F(Vec3Suite, ConstBracketGetter) {
    const sgf::type::Vec3 oVec(2, 3, 4);

    ASSERT_EQ(2, oVec[0]);
    ASSERT_EQ(3, oVec[1]);
    ASSERT_EQ(4, oVec[2]);
}

TEST_F(Vec3Suite, PlusTwoVec) {
    sgf::type::Vec3 oVec1(1, 2, 3);
    sgf::type::Vec3 oVec2(3, 4, 5);

    oVec1.plus(oVec2);
    
    ASSERT_EQ(4, oVec1.x);
    ASSERT_EQ(6, oVec1.y);
    ASSERT_EQ(8, oVec1.z);
    ASSERT_EQ(3, oVec2.x);
    ASSERT_EQ(4, oVec2.y);
    ASSERT_EQ(5, oVec2.z);
}

TEST_F(Vec3Suite, PlusVecItself) {
    sgf::type::Vec3 oVec(1, 2, 3);

    oVec.plus(oVec);
    
    ASSERT_EQ(2, oVec.x);
    ASSERT_EQ(4, oVec.y);
    ASSERT_EQ(6, oVec.z);
}

TEST_F(Vec3Suite, MinusTwoVec) {
    sgf::type::Vec3 oVec1(1, 2, 3);
    sgf::type::Vec3 oVec2(3, 4, 5);

    oVec1.minus(oVec2);
    
    ASSERT_EQ(-2, oVec1.x);
    ASSERT_EQ(-2, oVec1.y);
    ASSERT_EQ(-2, oVec1.z);
    ASSERT_EQ(3, oVec2.x);
    ASSERT_EQ(4, oVec2.y);
    ASSERT_EQ(5, oVec2.z);
}

TEST_F(Vec3Suite, MinusVecItself) {
    sgf::type::Vec3 oVec(1, 2, 3);

    oVec.minus(oVec);
    
    ASSERT_EQ(0, oVec.x);
    ASSERT_EQ(0, oVec.y);
    ASSERT_EQ(0, oVec.z);
}

TEST_F(Vec3Suite, MultiplyVec) {
    sgf::type::Vec3 oVec(1, 2, 3);

    oVec.multiply(5);

    ASSERT_EQ(5, oVec.x);
    ASSERT_EQ(10, oVec.y);
    ASSERT_EQ(15, oVec.z);
}

TEST_F(Vec3Suite, DivideVec) {
    sgf::type::Vec3 oVec(1, 2, 3);

    oVec.divide(5);

    ASSERT_FLOAT_EQ(0.2f, oVec.x);
    ASSERT_FLOAT_EQ(0.4f, oVec.y);
    ASSERT_FLOAT_EQ(0.6f, oVec.z);
}

TEST_F(Vec3Suite, TwoEqualItSelf) {
    sgf::type::Vec3 oVec(2, 3, 4);

    ASSERT_TRUE(oVec.equal(oVec));
}

TEST_F(Vec3Suite, TwoEqualVec) {
    sgf::type::Vec3 oVec1(2, 3, 4);
    sgf::type::Vec3 oVec2(2, 3, 4);
    
    ASSERT_TRUE(oVec1.equal(oVec2));
}

TEST_F(Vec3Suite, TwoNonEqualVec) {
    sgf::type::Vec3 oVec1(2, 3, 4);
    sgf::type::Vec3 oVec2(2, 4, 6);
    
    ASSERT_FALSE(oVec1.equal(oVec2));
}

TEST_F(Vec3Suite, CastToGLMVec) {
    sgf::type::Vec3 oSGFVec(1, 2, 3);
    glm::vec3& rGLMVec = sgf::type::toGLM(oSGFVec);

    ASSERT_EQ(1, rGLMVec.x);
    ASSERT_EQ(2, rGLMVec.y);
    ASSERT_EQ(3, rGLMVec.z);
}

TEST_F(Vec3Suite, CastToGLMVecIsSameAddress) {
    sgf::type::Vec3 oSGFVec(1, 2, 3);
    glm::vec3& rGLMVec = sgf::type::toGLM(oSGFVec);

    rGLMVec.x = 3;
    rGLMVec.y = 4;
    rGLMVec.z = 5;
    
    ASSERT_EQ(3, oSGFVec.x);
    ASSERT_EQ(4, oSGFVec.y);
    ASSERT_EQ(5, oSGFVec.z);
}

TEST_F(Vec3Suite, CastFromGLMVec) {
    glm::vec3 oGLMVec(1, 2, 3);
    sgf::type::Vec3& rSGFVec = sgf::type::toSGF(oGLMVec);

    ASSERT_EQ(1, rSGFVec.x);
    ASSERT_EQ(2, rSGFVec.y);
    ASSERT_EQ(3, rSGFVec.z);
}

TEST_F(Vec3Suite, CastFromGLMVecIsSameAddress) {
    glm::vec3 oGLMVec(1, 2, 3);
    sgf::type::Vec3& rSGFVec = sgf::type::toSGF(oGLMVec);

    rSGFVec.x = 3;
    rSGFVec.y = 4;
    rSGFVec.z = 5;
    
    ASSERT_EQ(3, oGLMVec.x);
    ASSERT_EQ(4, oGLMVec.y);
    ASSERT_EQ(5, oGLMVec.z);
}
