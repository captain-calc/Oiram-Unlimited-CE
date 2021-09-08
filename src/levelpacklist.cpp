// Name:    Captain Calc
// Date:    August 5, 2021
// File:    levelpacklist.cpp
// Purpose: This file provides the definitions of the LevelPackList class
//          member functions declared in levelpacklist.h.


#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <fileioc.h>
#include <graphx.h>
#include <keypadc.h>
#include <tice.h>

#include "asmutil.h"
#include "colors.h"
#include "cutil.h"
#include "defines.h"
#include "gui.h"
#include "levelpacklist.h"


void LevelPackList::Update()
{
  void *search_pos = 0;
  const char search_str[] = {'\xAB', '\xCD', '\x00'};
  char *appvar_name;
  
  // Set the number of packs to zero because we are updating the entire list
  // from scratch.
  m_NumPacks = 0;
  
  while ((appvar_name = ti_Detect(&search_pos, search_str)))
  {
    m_PackNames[m_NumPacks] = new char [PACK_NAME_LEN];
    memset(m_PackNames[m_NumPacks], '\0', PACK_NAME_LEN);
    strncpy(m_PackNames[m_NumPacks], appvar_name, PACK_NAME_LEN - 1);
    
    m_NumPacks++;
  }
  
  return;
}


void LevelPackList::Run()
{
  sk_key_t key;
  
  kb_Scan();
  key = asm_GetCSC();
  
  if ((key == sk_Up) && m_Index)
    m_Index--;
  
  if ((key == sk_Down) && (m_Index < m_NumPacks - 1))
    m_Index++;
  
  return;
}


void LevelPackList::Paint()
{
  ti_var_t slot;
  
  gfx_SetColor(GUI::GetBGColor());
  
  gfx_FillRectangle_NoClip(m_XPOS, m_YPOS - 15, m_WIDTH, m_HEIGHT + 35);
  
  gfx_SetColor(color_BLUE);
  
  gfx_Rectangle_NoClip(
    m_XPOS,
    m_YPOS,
    m_WIDTH,
    m_HEIGHT
  );
  
  gfx_Rectangle_NoClip(
    m_XPOS + 1,
    m_YPOS + 1,
    m_WIDTH - 2,
    m_HEIGHT - 2
  );
  
  gfx_FillTriangle_NoClip(
    m_XPOS + 2,
    m_YPOS + 2,
    m_XPOS + 10,
    m_YPOS + m_HEIGHT / 2,
    m_XPOS + 2,
    m_YPOS + m_HEIGHT - 2
  );
  
  gfx_FillTriangle_NoClip(
    m_XPOS + m_WIDTH - 2,
    m_YPOS + 2,
    m_XPOS + m_WIDTH - 10,
    m_YPOS + m_HEIGHT / 2,
    m_XPOS + m_WIDTH - 2,
    m_YPOS + m_HEIGHT - 2
  );
  
  if (m_Index)
    cutil_PrintCentered(m_PackNames[m_Index - 1], m_YPOS - 10);
  
  cutil_PrintCentered(m_PackNames[m_Index], m_YPOS + 6);
  
  if (m_Index < m_NumPacks - 1)
    cutil_PrintCentered(m_PackNames[m_Index + 1], m_YPOS + 25);
    
  if ((slot = ti_Open(m_PackNames[m_Index], "r")))
  {
    gfx_SetColor(GUI::GetBGColor());
    gfx_FillRectangle_NoClip(0, 195, LCD_WIDTH, 10);
    gfx_PrintStringXY("Title: ", 5, 195);
    gfx_PrintString((char *)cutil_GetPackPointer(slot));
    ti_Close(slot);
  }
  
  gfx_PrintStringXY("[2nd]/[enter]:  Edit pack/save changes", 5, 210);
  gfx_PrintStringXY("[clear]:  Exit w/o saving changes", 5, 220);
  gfx_PrintStringXY("Password-protected levels not shown", 5, 230);
  
  return;
}


char *LevelPackList::GetPackName(const uint8_t i) const
{
  char *pack_name = NULL;
  
  if (i < m_NumPacks)
    pack_name = m_PackNames[i];
  
  return pack_name;
}


LevelPackList::~LevelPackList()
{
  for (uint8_t i = 0; i < m_NumPacks; i++)
  {
    delete [] m_PackNames[i];
  }
}