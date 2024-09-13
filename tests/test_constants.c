#include "../lib/unity/src/unity.h"  // The Unity test framework
#include "../src/constants.h"  // Adjust the path as necessary
#include "test_constants.h"

void setUp(void) {
    // Set up code, if needed
}

void tearDown(void) {
    // Tear down code, if needed
}

void test_PROGRAM_NAME(void) {
    TEST_ASSERT_EQUAL_STRING("ez80op", PROGRAM_NAME);
}

void test_GIT_REPOSITORY(void) {
    TEST_ASSERT_EQUAL_STRING("https://github.com/andymccall/ez80op", GIT_REPOSITORY);
}

void test_GIT_INFO(void) {
    TEST_ASSERT_EQUAL_STRING("unknown", GIT_INFO);
}

void test_BUILD_YEAR(void) {
    TEST_ASSERT_EQUAL_STRING("2024", BUILD_YEAR);
}

void test_AUTHOR(void) {
    TEST_ASSERT_EQUAL_STRING("Andy McCall", AUTHOR);
}