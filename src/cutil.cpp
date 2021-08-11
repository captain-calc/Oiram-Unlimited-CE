// Name:    Captain Calc
// Date:    August 10, 2021
// File:    cutil.cpp
// Purpose: This file provides the definitions of the functions declared in
//          cutil.h.


#include <stdint.h>

#include <fileioc.h>
#include <graphx.h>
#include <tice.h>

#include "cutil.h"


void cutil_PrintCentered(const char *s, const uint8_t y_pos)
{
  gfx_PrintStringXY(s, (LCD_WIDTH / 2) - (gfx_GetStringWidth(s) / 2), y_pos);
  return;
}


uint8_t *cutil_GetPackPointer(ti_var_t slot)
{
    return (uint8_t*)ti_GetDataPtr(slot) + 2;
}