// Name:    Captain Calc
// Date:    August 9, 2021
// File:    asmutil.h
// Purpose: asmutil provides common assembly routines used by more than one
//          file.


#ifndef ASMUTIL_H
#define ASMUTIL_H


#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


// Description: asm_GetCSC() returns the sk_key_t code for a single keypress.
//              It combines the speed of a kb_Data register check with the
//              convenience of the single sk_key_t code. Note: This routine
//              cannot detect simultaneous keypresses. Use multiple kb_Data
//              checks to detect simultaneous keypresses.
// Pre:         None
// Post:        sk_key_t code returned if key pressed. If no key was pressed,
//              0 returned.
int8_t asm_GetCSC(void);


#ifdef __cplusplus
}
#endif

#endif