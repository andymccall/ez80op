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

#ifndef CONFIG_H
#define CONFIG_H

// #ifndef CEDEV
// #include <stdint.h>
// typedef int32_t int24_t;
// typedef uint32_t uint24_t;
// #endif

#ifdef _MSC_VER
#define strncasecmp _strnicmp
#define strcasecmp _stricmp
#pragma warning(disable:4996)			// 'strcpy': This function or variable may be unsafe. Consider using strcpy_s instead
#pragma warning(disable:4267)			// conversion from 'size_t' to 'int', possible loss of data
#pragma warning(disable:4244)			// conversion from '__int64' to 'uint16_t', possible loss of data
#endif

#define VERSION                       0
#define REVISION                      1
#endif // CONFIG_H