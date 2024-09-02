/* 
/ Title:		   ez80op
/
/ Description:     opcode typdef
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

#include "opcode.h"

opcode *createOpcode(int number,
                     char *name, 
                     char *description, 
                     char *conditionBits) {

  // Allocate memory for the pointers themselves and other elements
  // in the struct.
  opcode *code = malloc(sizeof(struct opcode));

  code->number = number; // Scalars (int, char, etc) can simply be copied

  // Must allocate memory for contents of pointers.  Here, strdup()
  // creates a new copy of name.  Another option:
  // p->name = malloc(strlen(name)+1);
  // strcpy(p->name, name);
  code->name = strdup(name);
  code->description = strdup(description);
  code->conditionBits = strdup(conditionBits);
  return code;
}