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
                     enum instructionType type,
                     char *name,
                     char *shortDescription,
                     char *longDescription) {
    opcode *code = malloc(sizeof(opcode));
    if (code == NULL) {
        return NULL; // Memory allocation error
    }

    code->number = number;
    code->type = type;
    code->name = strdup(name);
    code->shortDescription = strdup(shortDescription);
    code->longDescription = strdup(longDescription);

    return code;
}

void freeOpcode(opcode *code) {
    if (code == NULL) {
        return; 
    }

    free(code->name);
    free(code->shortDescription);
    free(code->longDescription);
    free(code);
}