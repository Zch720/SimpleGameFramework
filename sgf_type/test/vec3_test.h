#include <gtest/gtest.h>
#include "sgf/type/vec3.h"
#include "sgf/type/casting/cast_vec3.h"

class Vec3Suite : public testing::Test {
};

TEST_F(Vec3Suite, CreateDefaultVec3) {
    sgf::Vec3 v;

    ASSERT_EQ(0, v.x);
    ASSERT_EQ(0, v.y);
    ASSERT_EQ(0, v.z);
}

TEST_F(Vec3Suite, CreateVec3WithOneScaleValue) {
    sgf::Vec3 v(5);

    ASSERT_EQ(5, v.x);
    ASSERT_EQ(5, v.y);
    ASSERT_EQ(5, v.z);
}

TEST_F(Vec3Suite, CreateVec3WithExactlyValue) {
    sgf::Vec3 v(1, 2, 3);

    ASSERT_EQ(1, v.x);
    ASSERT_EQ(2, v.y);
    ASSERT_EQ(3, v.z);
}

TEST_F(Vec3Suite, Plus) {
    sgf::Vec3 v(1, 2, 3);

    v.plus(sgf::Vec3(4, 5, 6));

    ASSERT_EQ(5, v.x);
    ASSERT_EQ(7, v.y);
    ASSERT_EQ(9, v.z);
}

TEST_F(Vec3Suite, Minus) {
    sgf::Vec3 v(1, 2, 3);

    v.minus(sgf::Vec3(4, 5, 6));

    ASSERT_EQ(-3, v.x);
    ASSERT_EQ(-3, v.y);
    ASSERT_EQ(-3, v.z);
}

TEST_F(Vec3Suite, Multiply) {
    sgf::Vec3 v(1, 2, 3);

    v.multiply(2);

    ASSERT_EQ(2, v.x);
    ASSERT_EQ(4, v.y);
    ASSERT_EQ(6, v.z);
}

TEST_F(Vec3Suite, Division) {
    sgf::Vec3 v(1, 2, 3);

    v.division(2);

    ASSERT_EQ(0.5, v.x);
    ASSERT_EQ(1, v.y);
    ASSERT_EQ(1.5, v.z);
}

TEST_F(Vec3Suite, EqualToSelf) {
    sgf::Vec3 v(1, 2, 3);

    ASSERT_TRUE(v.equal(v));
}

TEST_F(Vec3Suite, Equal) {
    sgf::Vec3 v(1, 2, 3);

    ASSERT_TRUE(v.equal(sgf::Vec3(1, 2, 3)));
}

TEST_F(Vec3Suite, NotEqual) {
    sgf::Vec3 v(1, 2, 3);

    ASSERT_FALSE(v.equal(sgf::Vec3()));
}

TEST_F(Vec3Suite, CastSgfVectorToGlmVector) {
    sgf::Vec3 v(1, 2, 3);

    glm::vec3 glmV = sgf::toGlm(v);

    ASSERT_EQ(1, glmV.x);
    ASSERT_EQ(2, glmV.y);
    ASSERT_EQ(3, glmV.z);
}

TEST_F(Vec3Suite, CastGlmVectorToSgfVector) {
    glm::vec3 v(1, 2, 3);

    sgf::Vec3 sgfV = sgf::toSgf(v);

    ASSERT_EQ(1, sgfV.x);
    ASSERT_EQ(2, sgfV.y);
    ASSERT_EQ(3, sgfV.z);
}
