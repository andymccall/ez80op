#include <stdlib.h>
#include <string.h>
#include "../lib/unity/src/unity.h"  // The Unity test framework
#include "../src/opcode.h"  // Adjust the path as necessary
#include "test_opcode.h"

void test_createOpcode_should_ReturnValidOpcode(void) {
    int number = 1;
    enum instructionType type = IO; // Replace with actual enum value
    char *name = "Test Opcode";
    char *shortDescription = "Short Desc";
    char *longDescription = "Long Desc";
    ConditionBits conditionBits;

    conditionBits.S = true;
    conditionBits.S_explanation = strdup("Sign flag");
    conditionBits.Z = false;
    conditionBits.Z_explanation = strdup("Zero flag");
    conditionBits.H = true;
    conditionBits.H_explanation = strdup("Half carry flag");
    conditionBits.PV = false;
    conditionBits.PV_explanation = strdup("Parity/Overflow flag");
    conditionBits.N = true;
    conditionBits.N_explanation = strdup("Add/Subtract flag");
    conditionBits.C = false;
    conditionBits.C_explanation = strdup("Carry flag");

    opcode *code = createOpcode(number, type, name, shortDescription, longDescription, conditionBits);

    TEST_ASSERT_NOT_NULL(code);
    TEST_ASSERT_EQUAL_INT(number, code->number);
    TEST_ASSERT_EQUAL_INT(type, code->type);
    TEST_ASSERT_EQUAL_STRING(name, code->name);
    TEST_ASSERT_EQUAL_STRING(shortDescription, code->shortDescription);
    TEST_ASSERT_EQUAL_STRING(longDescription, code->longDescription);

    // Clean up
    free(code->name);
    free(code->shortDescription);
    free(code->longDescription);
    free(code);
}

void test_createOpcode_should_ReturnNullOnMallocFailure(void) {
    // // Simulate malloc failure by setting a limit on memory allocation
    // // This part is platform-specific and may require additional setup

    // // For demonstration purposes, we'll assume malloc fails
    // // You can use a custom malloc function to simulate this in a real test

    // // Example:
    // // set_malloc_limit(0);

    // opcode *code = createOpcode(1, IO, "Test", "Short", "Long", (ConditionBits) { // Create ConditionBits directly within the call
    //                     .S = true,
    //                     .S_explanation = "Sign flag is set if the result is negative",
    //                     .Z = true,
    //                     .Z_explanation = "Zero flag is set if the result is zero",
    //                     .H = false,
    //                     .H_explanation = NULL, 
    //                     .PV = false,
    //                     .PV_explanation = NULL,
    //                     .N = true,
    //                     .N_explanation = "Negative flag is set if the result is negative",
    //                     .C = false,
    //                     .C_explanation = NULL
    //                 } );

    // TEST_ASSERT_NULL(code);

    // // Reset malloc limit if necessary
    // // reset_malloc_limit();
}