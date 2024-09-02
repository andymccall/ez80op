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

#include "opcode.h"

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

typedef struct     {
  int number;
  char *name;
  char *description;
  char *conditionBits;
} opcode;

opcode *createOpcode(int number,
                     char *name,
                     char *description,
                     char *conditionBits);
 
#endif /* !_OPCODE_H_ */