/* 
/ Title:		   ez80op
/
/ Description:     opcode typdef implementation
/
/ Author:          Andy McCall, mailme@andymccall.co.uk
/
/ Created:		   Fri 30 Aug 15:37:58 BST 2024
/ Last Updated:	   
/
/ Modinfo:
*/

#if !defined __STDC__ || !__STDC__
/* This is a separate conditional since some stdc systems
   reject `defined (const)'.  */
# ifndef const
#  define const
# endif
#endif

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "opcode.h"

opcode *createOpcode(int number,
                     enum instructionType type,
                     char *name,
                     char *shortDescription,
                     char *longDescription,
                     ConditionBits conditionBits) {

    opcode *code = malloc(sizeof(opcode));
    if (code == NULL) {
        return NULL; 
    }

    code->number = number;
    code->type = type;
    code->name = strdup(name);
    code->shortDescription = strdup(shortDescription);
    code->longDescription = strdup(longDescription);

    // Initialize the conditionBits struct
    code->conditionBits.S = conditionBits.S;
    code->conditionBits.S_explanation = conditionBits.S_explanation ? strdup(conditionBits.S_explanation) : NULL;
    code->conditionBits.Z = conditionBits.Z;
    code->conditionBits.Z_explanation = conditionBits.Z_explanation ? strdup(conditionBits.Z_explanation) : NULL;
    code->conditionBits.H = conditionBits.H;
    code->conditionBits.H_explanation = conditionBits.H_explanation ? strdup(conditionBits.H_explanation) : NULL;
    code->conditionBits.PV = conditionBits.PV;
    code->conditionBits.PV_explanation = conditionBits.PV_explanation ? strdup(conditionBits.PV_explanation) : NULL;
    code->conditionBits.N = conditionBits.N;
    code->conditionBits.N_explanation = conditionBits.N_explanation ? strdup(conditionBits.N_explanation) : NULL;
    code->conditionBits.C = conditionBits.C;
    code->conditionBits.C_explanation = conditionBits.C_explanation ? strdup(conditionBits.C_explanation) : NULL;

    return code;

}

void freeOpcode(opcode *code) {
    if (code == NULL) {
        return; 
    }

    free(code->name);
    free(code->shortDescription);
    free(code->longDescription);

    // Free explanation strings only if the corresponding condition bit is affected
    if (code->conditionBits.S) {
        free(code->conditionBits.S_explanation);
    }
    if (code->conditionBits.Z) {
        free(code->conditionBits.Z_explanation);
    }
    if (code->conditionBits.H) {
        free(code->conditionBits.H_explanation);
    }
    if (code->conditionBits.PV) {
        free(code->conditionBits.PV_explanation);
    }
    if (code->conditionBits.N) {
        free(code->conditionBits.N_explanation);
    }
    if (code->conditionBits.C) {
        free(code->conditionBits.C_explanation);
    }
    free(code);
}

void printOpcode(opcode *code) {
    if (code == NULL) {
        printf("Invalid opcode (NULL pointer)\n");
        return;
    }

    printf("%s\n", code->name);
    printf("    %s\n", code->shortDescription);
    printf("Description\n");
    printf("    %s\n", code->longDescription);

    printf("Condition Bits Affected\n");

    if (code->conditionBits.S) {
        printf("    S: %s\n", code->conditionBits.S_explanation);
    } 

    if (code->conditionBits.Z) {
        printf("    Z: %s\n", code->conditionBits.Z_explanation);
    } 

    if (code->conditionBits.H) {
        printf("    H: %s\n", code->conditionBits.H_explanation);
    }

    if (code->conditionBits.PV) {
        printf("    PV: %s\n", code->conditionBits.PV_explanation);
    }

    if (code->conditionBits.N) {
        printf("    N: %s\n", code->conditionBits.N_explanation);
    } 

    if (code->conditionBits.C) {
        printf("    C: %s\n", code->conditionBits.C_explanation);
    } 
}