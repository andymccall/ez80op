#ifndef _DATA_H_
#define _DATA_H_

#include "opcode.h"

int saveOpcodesToFile(const char *filename, opcode **opcodes, int numOpcodes);
int loadOpcodesFromFile(const char *filename, opcode ***opcodes, int *numOpcodes);

#endif /* !_DATA_H_ */