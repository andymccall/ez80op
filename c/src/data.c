#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

int saveOpcodesToFile(const char *filename, opcode **opcodes, int numOpcodes) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        return -1; // Error opening file
    }

    // Write the number of opcodes
    fwrite(&numOpcodes, sizeof(int), 1, fp);

    for (int i = 0; i < numOpcodes; i++) {
        opcode *code = opcodes[i];

        // Write the opcode's data
        fwrite(&code->number, sizeof(int), 1, fp);

        fwrite(&code->type, sizeof(int), 1, fp);

        size_t nameLength = strlen(code->name) + 1; // +1 for null terminator
        fwrite(&nameLength, sizeof(size_t), 1, fp);
        fwrite(code->name, 1, nameLength, fp);

        size_t shortDescriptionLength = strlen(code->shortDescription) + 1;
        fwrite(&shortDescriptionLength, sizeof(size_t), 1, fp);
        fwrite(code->shortDescription, 1, shortDescriptionLength, fp);

        size_t longDescriptionLength = strlen(code->longDescription) + 1;
        fwrite(&longDescriptionLength, sizeof(size_t), 1, fp);
        fwrite(code->longDescription, 1, longDescriptionLength, fp);;
    }

    fclose(fp);
    return 0; // Success
}

int loadOpcodesFromFile(const char *filename, opcode ***opcodes, int *numOpcodes) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        return -1; // Error opening file
    }

    // Read the number of opcodes
    fread(numOpcodes, sizeof(int), 1, fp);

    // Allocate memory for the opcode array
    *opcodes = malloc(sizeof(opcode *) * (*numOpcodes));
    if (*opcodes == NULL) {
        fclose(fp);
        return -1; // Memory allocation error
    }

    for (int i = 0; i < *numOpcodes; i++) {
        // Read the opcode's data
        int number;
        fread(&number, sizeof(int), 1, fp);

        enum instructionType type;
        fread(&type, sizeof(int), 1, fp);

        size_t nameLength;
        fread(&nameLength, sizeof(size_t), 1, fp);
        char *name = malloc(nameLength);
        fread(name, 1, nameLength, fp);

        size_t shortDescriptionLength;
        fread(&shortDescriptionLength, sizeof(size_t), 1, fp);
        char *shortDescription = malloc(shortDescriptionLength);
        fread(shortDescription, 1, shortDescriptionLength, fp);

        size_t longDescriptionLength;
        fread(&longDescriptionLength, sizeof(size_t), 1, fp);
        char *longDescription = malloc(longDescriptionLength);
        fread(longDescription, 1, longDescriptionLength, fp);

        // Create the opcode and add it to the array
        (*opcodes)[i] = createOpcode(number, type, name, shortDescription, longDescription);

        // Free the temporary buffers
        free(name);
        free(shortDescription);
        free(longDescription);
    }

    fclose(fp);
    return 0; // Success
}