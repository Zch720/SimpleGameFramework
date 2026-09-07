#include <gtest/gtest.h>

#include "./vec3_test.h"
#include "./mat2_test.h"
#include "./mat2x3_test.h"

int main(int argc, char * argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
