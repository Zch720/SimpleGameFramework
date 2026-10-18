#include <gtest/gtest.h>

#include "./vec2_test.h"
#include "./vec3_test.h"
#include "./vec4_test.h"
#include "./mat2_test.h"
#include "./mat3_test.h"
#include "./mat4_test.h"
#include "./mat2x3_test.h"
#include "./mat2x4_test.h"
#include "./mat3x2_test.h"
#include "./mat3x4_test.h"
#include "./mat4x2_test.h"
#include "./mat4x3_test.h"

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
