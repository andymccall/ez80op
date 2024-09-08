#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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

        // Write the existing opcode data 
        fwrite(&code->number, sizeof(int), 1, fp);
        fwrite(&code->type, sizeof(int), 1, fp);

        size_t nameLength = strlen(code->name) + 1; 
        fwrite(&nameLength, sizeof(size_t), 1, fp);
        fwrite(code->name, 1, nameLength, fp);

        size_t shortDescriptionLength = strlen(code->shortDescription) + 1;
        fwrite(&shortDescriptionLength, sizeof(size_t), 1, fp);
        fwrite(code->shortDescription, 1, shortDescriptionLength, fp);

        size_t longDescriptionLength = strlen(code->longDescription) + 1;
        fwrite(&longDescriptionLength, sizeof(size_t), 1, fp);
        fwrite(code->longDescription, 1, longDescriptionLength, fp);

        // Write the conditionBits data
        fwrite(&code->conditionBits.S, sizeof(bool), 1, fp);
        if (code->conditionBits.S) { 
            size_t sExplanationLength = strlen(code->conditionBits.S_explanation) + 1;
            fwrite(&sExplanationLength, sizeof(size_t), 1, fp);
            fwrite(code->conditionBits.S_explanation, 1, sExplanationLength, fp);
        }

        fwrite(&code->conditionBits.Z, sizeof(bool), 1, fp);
        if (code->conditionBits.Z) { 
            size_t zExplanationLength = strlen(code->conditionBits.Z_explanation) + 1;
            fwrite(&zExplanationLength, sizeof(size_t), 1, fp);
            fwrite(code->conditionBits.Z_explanation, 1, zExplanationLength, fp);
        }

        fwrite(&code->conditionBits.H, sizeof(bool), 1, fp);
        if (code->conditionBits.H) { 
            size_t hExplanationLength = strlen(code->conditionBits.H_explanation) + 1;
            fwrite(&hExplanationLength, sizeof(size_t), 1, fp);
            fwrite(code->conditionBits.H_explanation, 1, hExplanationLength, fp);
        }

        fwrite(&code->conditionBits.PV, sizeof(bool), 1, fp);
        if (code->conditionBits.PV) { 
            size_t pvExplanationLength = strlen(code->conditionBits.PV_explanation) + 1;
            fwrite(&pvExplanationLength, sizeof(size_t), 1, fp);
            fwrite(code->conditionBits.PV_explanation, 1, pvExplanationLength, fp);
        }

        fwrite(&code->conditionBits.N, sizeof(bool), 1, fp);
        if (code->conditionBits.N) { 
            size_t nExplanationLength = strlen(code->conditionBits.N_explanation) + 1;
            fwrite(&nExplanationLength, sizeof(size_t), 1, fp);
            fwrite(code->conditionBits.N_explanation, 1, nExplanationLength, fp);
        }

        fwrite(&code->conditionBits.C, sizeof(bool), 1, fp);
        if (code->conditionBits.C) { 
            size_t cExplanationLength = strlen(code->conditionBits.C_explanation) + 1;
            fwrite(&cExplanationLength, sizeof(size_t), 1, fp);
            fwrite(code->conditionBits.C_explanation, 1, cExplanationLength, fp);
        }
    }

    fclose(fp);
    return 0; 
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
        // Read the existing opcode data 
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

        // Read the conditionBits data
        ConditionBits condBits = {0};

        fread(&condBits.S, sizeof(bool), 1, fp);
        if (condBits.S) { 
            size_t sExplanationLength;
            fread(&sExplanationLength, sizeof(size_t), 1, fp);
            condBits.S_explanation = malloc(sExplanationLength);
            fread(condBits.S_explanation, 1, sExplanationLength, fp);
        }

        fread(&condBits.Z, sizeof(bool), 1, fp);
        if (condBits.Z) { 
            size_t zExplanationLength;
            fread(&zExplanationLength, sizeof(size_t), 1, fp);
            condBits.Z_explanation = malloc(zExplanationLength);
            fread(condBits.Z_explanation, 1, zExplanationLength, fp);
        }

        fread(&condBits.H, sizeof(bool), 1, fp);
        if (condBits.H) { 
            size_t hExplanationLength;
            fread(&hExplanationLength, sizeof(size_t), 1, fp);
            condBits.H_explanation = malloc(hExplanationLength);
            fread(condBits.H_explanation, 1, hExplanationLength, fp);
        }

        fread(&condBits.PV, sizeof(bool), 1, fp);
        if (condBits.PV) { 
            size_t pvExplanationLength;
            fread(&pvExplanationLength, sizeof(size_t), 1, fp);
            condBits.PV_explanation = malloc(pvExplanationLength);
            fread(condBits.PV_explanation, 1, pvExplanationLength, fp);
        }

        fread(&condBits.N, sizeof(bool), 1, fp);
        if (condBits.N) { 
            size_t nExplanationLength;
            fread(&nExplanationLength, sizeof(size_t), 1, fp);
            condBits.N_explanation = malloc(nExplanationLength);
            fread(condBits.N_explanation, 1, nExplanationLength, fp);
        }

        fread(&condBits.C, sizeof(bool), 1, fp);
        if (condBits.C) { 
            size_t cExplanationLength;
            fread(&cExplanationLength, sizeof(size_t), 1, fp);
            condBits.C_explanation = malloc(cExplanationLength);
            fread(condBits.C_explanation, 1, cExplanationLength, fp);
        }

        // Create the opcode and add it to the array
        (*opcodes)[i] = createOpcode(number, type, name, shortDescription, longDescription, condBits);

        // Free the temporary buffers
        free(name);
        free(shortDescription);
        free(longDescription);

        // Free the memory allocated for condition bit explanations 
        if (condBits.S) free(condBits.S_explanation);
        if (condBits.Z) free(condBits.Z_explanation);
        if (condBits.H) free(condBits.H_explanation);
        if (condBits.PV) free(condBits.PV_explanation);
        if (condBits.N) free(condBits.N_explanation);
        if (condBits.C) free(condBits.C_explanation);
    }

    fclose(fp);
    return 0; 
}
