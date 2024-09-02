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
#include "opcode.h"

opcode *createOpcode(int number,
                     char *name, 
                     char *description, 
                     char *conditionBits) {

  opcode *code = malloc(sizeof(opcode));

  code->number = number; // Scalars (int, char, etc) can simply be copied

  code->name = strdup(name);
  code->description = strdup(description);
  code->conditionBits = strdup(conditionBits);

  return code;

}