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
#include <stdbool.h>
#include <stdint.h>
#include "getopt.h"
#include "globals.h"
#include "config.h"

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

int main(int argc, char *argv[]) {
    int opt;
    
    #ifdef UNIX
    uint8_t errorexit = 2;
    #else
    uint8_t errorexit = 0;
    #endif
    
    coloroutput = true;
    
    while ((opt = getopt(argc, argv, "-:vhc:")) != -1) {
        switch(opt) {
            case 'c':
                coloroutput = false;
                break;
            case 'v':
                printVersion();
                break;
            case 'h':
                printHelp();
                return 0;
        }
    }
      
    return 0;
}
