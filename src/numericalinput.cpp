// Name:    Captain Calc
// Date:    August 9, 2021
// File:    numericalinput.cpp
// Purpose: This file contains the definitions for the member functions of the
//          NumericalInput class defined in numericalinput.h.


#include <stdint.h>
#include <stdio.h>

#include <keypadc.h>
#include <graphx.h>
#include <tice.h>

#include "asmutil.h"
#include "colors.h"
#include "numericalinput.h"
#include "timer.h"


void NumericalInput::p_InitFieldCoords()
{
  m_BufferXPos = m_XPos + 2;
  m_BufferYPos = m_YPos + 3;
  m_CursorXPos = m_XPos + 2;
  m_CursorYPos = m_YPos + 2;
  m_CursorWidth = 4;
  m_CursorHeight = m_FieldHeight - 4;
  return;
}


void NumericalInput::p_Paint()
{
  gfx_SetColor(NUMERICAL_INPUT_FIELD_BORDER_COLOR);
  gfx_Rectangle_NoClip(m_XPos, m_YPos, m_FieldWidth, m_FieldHeight);
  gfx_SetColor(NUMERICAL_INPUT_FIELD_BG_COLOR);
  gfx_FillRectangle_NoClip(
    m_XPos + 1, m_YPos + 1, m_FieldWidth - 2, m_FieldHeight - 2
  );
  
  gfx_SetTextBGColor(NUMERICAL_INPUT_FIELD_BG_COLOR);
  gfx_SetTextFGColor(NUMERICAL_INPUT_FIELD_BORDER_COLOR);
  gfx_SetTextTransparentColor(NUMERICAL_INPUT_FIELD_BG_COLOR);
  
  gfx_PrintStringXY(GetBuffer(), m_BufferXPos, m_BufferYPos);
  
  if (m_Blink)
    gfx_SetColor(NUMERICAL_INPUT_FIELD_BG_COLOR);
  else
    gfx_SetColor(NUMERICAL_INPUT_CURSOR_COLOR);
  
  gfx_FillRectangle_NoClip(m_CursorXPos, m_CursorYPos, m_CursorWidth, m_CursorHeight);
  return;
}


NumericalInput::NumericalInput(const uint24_t x, const uint8_t y):
  InputBuffer(NUMERICAL_INPUT_STD_BUFFER_SIZE),
  FocusableWidget(),
  m_XPos(x),
  m_YPos(y),
  m_FieldWidth(NUMERICAL_INPUT_STD_FIELD_WIDTH),
  m_FieldHeight(NUMERICAL_INPUT_STD_FIELD_HEIGHT),
  m_MinValue(0),
  m_MaxValue(999),
  m_Blink(true)
{
  p_InitFieldCoords();
}


NumericalInput::NumericalInput(
  const uint8_t size,
  const uint24_t x,
  const uint8_t y,
  const uint24_t width,
  const uint8_t height
):
  InputBuffer(size),
  FocusableWidget(),
  m_XPos(x),
  m_YPos(y),
  m_FieldWidth(width),
  m_FieldHeight(height),
  m_MinValue(0),
  m_MaxValue(999),
  m_Blink(true)
{
  p_InitFieldCoords();
}


bool NumericalInput::AddChar(const char c)
{
  bool added = false;
  
  if (InputBuffer::AddChar(c))
  {
    m_CursorXPos += gfx_GetCharWidth(c);
    added = true;
  }
  
  return added;
}


char NumericalInput::RemoveChar()
{
  char removed_char;
  
  if ((removed_char = InputBuffer::RemoveChar()))
  {
    m_CursorXPos -= gfx_GetCharWidth(removed_char);
  }
  
  return removed_char;
}


void NumericalInput::EmptyBuffer()
{
  while (RemoveChar());
  return;
}


void NumericalInput::ForceSetNumberTo(const long value)
{
  char *buffer = new char[InputBuffer::GetSize() - 1];
  
  EmptyBuffer();
  sprintf(buffer, "%ld", value);
  InputBuffer::ForceSetBufferTo(buffer);
  m_CursorXPos += gfx_GetStringWidth(buffer);
  
  delete [] buffer;
  return;
}


// TODO: Replace with more efficient algorithm.
bool NumericalInput::KeyToNumeral(const sk_key_t key, char *numeral) const
{
  bool is_numeral = true;
  
  switch(key)
  {
    case sk_0:
      *numeral = '0';
      break;
    
    case sk_1:
      *numeral = '1';
      break;
    
    case sk_2:
      *numeral = '2';
      break;
    
    case sk_3:
      *numeral = '3';
      break;
    
    case sk_4:
      *numeral = '4';
      break;
    
    case sk_5:
      *numeral = '5';
      break;
    
    case sk_6:
      *numeral = '6';
      break;
    
    case sk_7:
      *numeral = '7';
      break;
    
    case sk_8:
      *numeral = '8';
      break;
    
    case sk_9:
      *numeral = '9';
      break;
    
    default:
      is_numeral = false;
  }
  
  return is_numeral;
}


void NumericalInput::Run()
{
  char numeral;
  sk_key_t key;
  
  kb_Scan();
  key = asm_GetCSC();
  
  if (KeyToNumeral(key, &numeral))
  {
    AddChar(numeral);
    
    if (GetValue() < m_MinValue)
      ForceSetNumberTo(m_MinValue);
    
    if (GetValue() > m_MaxValue)
      ForceSetNumberTo(m_MaxValue);
  }
  
  if (key == sk_Del)
    RemoveChar();
  
  return;
}


void NumericalInput::Paint()
{
  if (Timer::IsExpired())
    m_Blink = !m_Blink;
  
  p_Paint();
  return;
}


void NumericalInput::UnfocusedPaint()
{
  // We cannot use Paint() because if the Timer expires at the same time this
  // paint executes, the cursor will be drawn, defeating the purpose of the
  // UnfocusedPaint().
  m_Blink = true;
  p_Paint();
  return;
}


bool NumericalInput::SetMinValue(const long min)
{
  bool set = false;
  
  if (min < m_MaxValue)
  {
    m_MinValue = min;
    set = true;
  }
  
  return set;
}


bool NumericalInput::SetMaxValue(const long max)
{
  bool set = false;
  
  if (max > m_MinValue)
  {
    m_MaxValue = max;
    set = true;
  }
  
  return set;
}


bool NumericalInput::IsValidValue()
{
  bool valid = false;
  long value = GetValue();
  
  if ((value >= m_MinValue) && (value <= m_MaxValue))
    valid = true;
  
  return valid;
}