// Name:    Captain Calc
// Date:    August 10, 2021
// File:    horizlistmenu.cpp
// Purpose: This file provides the definitions of the HorizListMenu class
//          member functions declared in horizlistmenu.h.


#include <graphx.h>
#include <keypadc.h>
#include <tice.h>

#include "asmutil.h"
#include "colors.h"
#include "gui.h"
#include "horizlistmenu.h"


// These defines are local to this file.
#define UNFOCUSED_CURSOR_COLOR  color_BLUE
#define FOCUSED_CURSOR_COLOR    color_LT_BLUE
#define SELECTED_TEXT_COLOR     color_BLACK
#define UNSELECTED_TEXT_COLOR   color_WHITE


void HorizListMenu::p_Paint()
{
  const uint8_t ITEM_GAP = 6;
  uint24_t x_pos = m_XPos;
  uint24_t item_width;
  
  for (uint8_t i = 0; i < m_Size; i++)
  {
    item_width = gfx_GetStringWidth(m_Items[i]);
    
    gfx_SetColor(GUI::GetBGColor());
    gfx_FillRectangle_NoClip(x_pos, m_YPos, item_width + 4, 11);
  
    gfx_SetColor(m_CursorColor);
    
    if (i == m_Index)
    {
      gfx_SetTextBGColor(m_CursorColor);
      gfx_SetTextTransparentColor(m_CursorColor);
      gfx_SetTextFGColor(SELECTED_TEXT_COLOR);
      gfx_FillRectangle_NoClip(x_pos, m_YPos, item_width + 4, 11);
    }
    else
    {
      gfx_SetTextBGColor(GUI::GetBGColor());
      gfx_SetTextTransparentColor(GUI::GetBGColor());
      gfx_SetTextFGColor(UNSELECTED_TEXT_COLOR);
    }
  
    gfx_PrintStringXY(m_Items[i], x_pos + 2, m_YPos + 2);
    
    x_pos += item_width + ITEM_GAP;
  }
  
  return;
}


HorizListMenu::HorizListMenu(
  const char *items[],
  const uint8_t size,
  const uint8_t index,
  const uint24_t x,
  const uint8_t y
):
  FocusableWidget(),
  m_CursorColor(UNFOCUSED_CURSOR_COLOR),
  m_Size(size),
  m_XPos(x),
  m_YPos(y)
{
  for (uint8_t i = 0; i < m_Size; i++)
    m_Items[i] = items[i];
  
  if (index < m_Size)
    m_Index = index;
  else
    m_Index = 0;
}


void HorizListMenu::Run()
{
  sk_key_t key;
  
  kb_Scan();
  key = asm_GetCSC();
  
  if ((key == sk_Left) && m_Index)
    m_Index--;
  
  if ((key == sk_Right) && (m_Index < m_Size - 1))
    m_Index++;
  
  // Only set the focused colors when the widget is run. If this were in
  // Paint(), then GUI::PaintAllFocusableWidgets() would paint this widget as
  // focused.
  m_CursorColor = FOCUSED_CURSOR_COLOR;
  
  return;
}


void HorizListMenu::Paint()
{
  p_Paint();
  return;
}


void HorizListMenu::UnfocusedPaint()
{
  m_CursorColor = UNFOCUSED_CURSOR_COLOR;
  p_Paint();
  return;
}