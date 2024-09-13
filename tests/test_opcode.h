#ifndef TEST_OPCODE_H
#define TEST_OPCODE_H

#include <stdlib.h>
#include <string.h>
#include "../lib/unity/src/unity.h"  // The Unity test framework
#include "../src/opcode.h"  // Adjust the path as necessary

void test_createOpcode_should_ReturnValidOpcode(void);
void test_createOpcode_should_ReturnNullOnMallocFailure(void);

#endif // TEST_OPCODE_H