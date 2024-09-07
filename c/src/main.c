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
#include "getopt.h"
#include "globals.h"
#include "config.h"
#include "opcode.h"
#include "data.h"

void printVersion(void) {
    printf("ez80op version %d.%d, (C)2024 - Andy McCall\r\n",VERSION,REVISION);
}

void printHelp(void) {
    printf("Usage: ez80asm <opcode> [OPTION]\n\r\r\n");
    printf("  -v\tList version information\r\n");
    printf("  -h\tList help information\r\n");
    printf("  -c\tNo color codes in output\r\n");
    printf("\r\n");
}

opcode* findOpcodeByName(opcode **opcodes, int numOpcodes, const char *targetName) {
    for (int i = 0; i < numOpcodes; i++) {
        if (strcmp(opcodes[i]->name, targetName) == 0) {
            return opcodes[i]; // Found the opcode
        }
    }
    return NULL; // Opcode not found
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

    // // Create some opcodes
    // opcode *opcodes[] = {
    //     createOpcode(1,
    //                 ARITHMETIC_INSTRUCTIONS,
    //                 "ADC",
    //                 "Add with Carry",
    //                 "The (HL) operand is an 8-bit value retrieved from the memory location specified by the contents of the multibyte register HL. This 8-bit value and the Carry Flag (C) are added to the contents of the accumulator, A. The result is stored in the accumulator."),
    //     createOpcode(2,
    //                 ARITHMETIC_INSTRUCTIONS,
    //                 "ADD",
    //                 "Add without Carry",
    //                 "The ir operand is any of IXH, IXL, IYH, or IYL. The ir operand is added to the contents of the accumulator, A. The result is stored in the accumulator.")
        
    // };
    // int numOpcodes = sizeof(opcodes) / sizeof(opcodes[0]);

    // // Save opcodes to file
    // if (saveOpcodesToFile("opcodes.dat", opcodes, numOpcodes) != 0) {
    //     fprintf(stderr, "Error saving opcodes to file.\n");
    //     return 1;
    // }

    // // Free the original opcodes (optional, if you don't need them anymore)
    // for (int i = 0; i < numOpcodes; i++) {
    //     freeOpcode(opcodes[i]);
    // }

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

        // // Use the loaded opcodes
        // for (int i = 0; i < loadedNumOpcodes; i++) {
        
        //     printf("%s\n",loadedOpcodes[i]->name);
        //     printf("   %s\n",loadedOpcodes[i]->shortDescription);
        //     printf("Description\n");
        //     printf("   %s\n",loadedOpcodes[i]->longDescription);
            
        //     freeOpcode(loadedOpcodes[i]);
        // }

        //const char *targetOpcodeName = first_argument;
        opcode *foundOpcode = findOpcodeByName(loadedOpcodes, loadedNumOpcodes, first_argument);

        if (foundOpcode != NULL) {
            printf("%s\n",foundOpcode->name);
            printf("   %s\n",foundOpcode->shortDescription);
            printf("Description\n");
            printf("   %s\n",foundOpcode->longDescription);

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
