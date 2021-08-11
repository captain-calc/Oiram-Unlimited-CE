// Name:    Captain Calc
// Date:    August 10, 2021
// File:    cutil.h
// Purpose: This file provides common C routines.


#ifndef CUTIL_H
#define CUTIL_H


#include <stdint.h>

#include <fileioc.h>


// Description: cutil_PrintCentered() prints a centered string.
// Pre:         <y_pos> must make the string fit onscreen. The string's width
//              must be less than the width of the screen.
// Post:        <s> printed centered onscreen.
void cutil_PrintCentered(const char *s, const uint8_t y_pos);


// Description: cutil_GetPackPointer() retrieves a pointer to the start of the
//              pack data for regular (non-password-protected) Oiram level
//              pack.
// Pre:         <slot> should be for a regular Oiram level pack.
// Post:        Pointer to start of pack data returned.
uint8_t *cutil_GetPackPointer(ti_var_t slot);

#endif