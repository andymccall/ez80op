/* 
/ Title:		   ez80op
/
/ Description:     opcode typdef header
/
/ Author:          Andy McCall, mailme@andymccall.co.uk
/
/ Created:		   Fri 30 Aug 15:37:58 BST 2024
/ Last Updated:	   
/
/ Modinfo:
*/

#ifndef _OPCODE_H_
#define _OPCODE_H_

/*
Example Opcode

Opcode: NOP, No Operation
Operation: No operation
Description: The CPU performs no operation during execution of this instruction
Condition Bits Affected: None
Attributes: 
Mnemonic Operand ADL Mode Cycle Opcode (hex)
NOP              X        1     00
*/

enum instructionType {
  ARITHMETIC_INSTRUCTIONS,
  BIT_MANIPULATION,
  BIT_SHIFTS,
  BLOCK_OPERATIONS,
  IO,
  LOAD_AND_EXCHANGE,
  LOGIC,
  PROGRAM_FLOW,
  PROCESSOR_CONTROL
};

typedef struct {
  int number;
  enum instructionType type;
  char *name;
  char *shortDescription;
  char *longDescription;
} opcode;

opcode *createOpcode(int number,
                     enum instructionType type,
                     char *name,
                     char *shortDescription,
                     char *longDescription);
 
void freeOpcode(opcode *code);

#endif /* !_OPCODE_H_ */