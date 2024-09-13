#include "test_constants.h"
#include "test_opcode.h"

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_createOpcode_should_ReturnValidOpcode);
    RUN_TEST(test_createOpcode_should_ReturnNullOnMallocFailure);
    RUN_TEST(test_PROGRAM_NAME);
    RUN_TEST(test_GIT_REPOSITORY);
    RUN_TEST(test_GIT_INFO);
    RUN_TEST(test_BUILD_YEAR);
    RUN_TEST(test_AUTHOR);
    return UNITY_END();
}