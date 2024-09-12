/* 
/ Title:		   ez80op
/
/ Description:     ex80op, main program code
/
/ Author:          Andy McCall, mailme@andymccall.co.uk
/
/ Created:		   Fri 30 Aug 15:37:58 BST 2024
/ Last Updated:	   
/
/ Modinfo:
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "getopt.h"
#include "globals.h"
#include "config.h"
#include "opcode.h"
#include "data.h"
#include "constants.h"

void printVersion(void) {
    printf("%s version %d.%d-%s, (C)%s - %s\r\n",PROGRAM_NAME,VERSION,REVISION,GIT_INFO,BUILD_YEAR,AUTHOR);
    printf("%s\r\n",GIT_REPOSITORY);
}

void printHelp(void) {
    printf("Usage: ez80asm <opcode> [OPTION]\n\r\r\n");
    printf("  -v\tList version information\r\n");
    printf("  -h\tList help information\r\n");
    printf("  -c\tNo color codes in output\r\n");
    printf("\r\n");
}

opcode* findOpcodeByName(opcode **opcodes, int numOpcodes, const char *targetName) {
    if (opcodes == NULL || targetName == NULL) {
        return NULL; // Handle invalid input
    }

    size_t targetNameLength = strlen(targetName);
    for (int i = 0; i < numOpcodes; i++) {
        if (strlen(opcodes[i]->name) != targetNameLength) {
            continue; // Skip opcodes with different name lengths for efficiency
        }

        // Case-insensitive comparison
        int match = 1; 
        for (size_t j = 0; j < targetNameLength; j++) {
            if (toupper(opcodes[i]->name[j]) != toupper(targetName[j])) {
                match = 0;
                break;
            }
        }

        if (match) {
            return opcodes[i];
        }
    }

    return NULL;
}

int main(int argc, char *argv[]) {

    int opt;
    char *first_argument = NULL;

    
    #ifdef UNIX
    uint8_t errorexit = 2;
    #else
    uint8_t errorexit = 0;
    #endif
    
    coloroutput = true;

    // Create some opcodes
    opcode *opcodes[] = {
            createOpcode(
                    1,               // Opcode number
                    ARITHMETIC_INSTRUCTIONS, // Instruction type
                    "ADD",            // Name
                    "Add registers",  // Short description
                    "Adds the contents of two registers and stores the result in the destination register", // Long description
                    (ConditionBits) { // Create ConditionBits directly within the call
                        .S = true,
                        .S_explanation = "Sign flag is set if the result is negative",
                        .Z = true,
                        .Z_explanation = "Zero flag is set if the result is zero",
                        .H = false,
                        .H_explanation = NULL, 
                        .PV = false,
                        .PV_explanation = NULL,
                        .N = true,
                        .N_explanation = "Negative flag is set if the result is negative",
                        .C = false,
                        .C_explanation = NULL
                    } 
                )
        
    };

    int numOpcodes = sizeof(opcodes) / sizeof(opcodes[0]);

    // Save opcodes to file
    if (saveOpcodesToFile("opcodes.dat", opcodes, numOpcodes) != 0) {
        fprintf(stderr, "Error saving opcodes to file.\n");
        return 1;
    }

    // Free the original opcodes (optional, if you don't need them anymore)
    for (int i = 0; i < numOpcodes; i++) {
        freeOpcode(opcodes[i]);
    }

    while ((opt = getopt(argc, argv, "vhc")) != -1) {
        switch(opt) {
            case 'c':
                coloroutput = false;
                break;
            case 'v':
                printVersion();
                return errorexit;
            case 'h':
                printHelp();
                return errorexit;
            case '?': // Handle unrecognized options
                fprintf(stderr, "Unrecognized option: -%c\n", optopt);
                return errorexit;
        }
    }


    if (optind < argc) {
        first_argument = argv[optind];

        // Load opcodes from file
        opcode **loadedOpcodes;
        int loadedNumOpcodes;
        if (loadOpcodesFromFile("opcodes.dat", &loadedOpcodes, &loadedNumOpcodes) != 0) {
            fprintf(stderr, "Error loading opcodes from file.\n");
            return 1;
        }

        //const char *targetOpcodeName = first_argument;
        opcode *foundOpcode = findOpcodeByName(loadedOpcodes, loadedNumOpcodes, first_argument);

        if (foundOpcode != NULL) {
            printOpcode(foundOpcode);

        } else {
            printf("Opcode '%s' not found.\n", first_argument);
        }

        // Free the loaded opcodes
        for (int i = 0; i < loadedNumOpcodes; i++) {       
            freeOpcode(loadedOpcodes[i]);
        }

        // Free the loaded opcode array
        free(loadedOpcodes);

    } else {
        printf("No opcode specified!\n\r\r\n"); 
        printHelp();
        return errorexit;
    }

    return 0;
}
