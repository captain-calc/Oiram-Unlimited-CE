// Name:    Captain Calc
// Date:    May 23, 2023
// File:    oiramanimation.cpp
// Purpose: This file contains the definitions for the member functions of the
//          OiramAnimation class declared in oiramanimation.h.


#include <sys/lcd.h>
#include <graphx.h>

#include "ccdbg.h"
#include "colors.h"
#include "gfx/gfx.h"
#include "levelpack.h"       // For FLAG_OIRAM_*
#include "oiramanimation.h"


void OiramAnimation::p_ChangeStride()
{
  if (m_Suit & FLAG_OIRAM_BIG)
  {
    if (m_Suit & FLAG_OIRAM_FIRE)
    {
      if (m_Sprite == oiram_0_fire)
        m_Sprite = oiram_1_fire;
      else
        m_Sprite = oiram_0_fire;
      
      return;
    }
    
    if (m_Suit & FLAG_OIRAM_RACOON)
    {
      if (m_Sprite == oiram_0_racoon)
        m_Sprite = oiram_1_racoon;
      else
        m_Sprite = oiram_0_racoon;
      
      return;
    }
    
    if (m_Sprite == oiram_0_big)
      m_Sprite = oiram_1_big;
    else
      m_Sprite = oiram_0_big;
    
    return;
  }
  
  // Default to small suit
  if (m_Sprite == oiram_0_small)
    m_Sprite = oiram_1_small;
  else
    m_Sprite = oiram_0_small;
  
  return;
}


OiramAnimation::OiramAnimation(
  const uint24_t x,
  const uint8_t y,
  const uint24_t width,
  const uint8_t height,
  const uint8_t suit,
  const bool invincibility
):
  UnfocusableWidget(),
  m_TailSprite(tail_right_0),
  m_GroundSprite(ground),
  m_GroundOffset(0),
  m_XPos(x),
  m_YPos(y),
  m_Width(width),
  m_Height(height),
  m_Suit(suit),
  m_Invincibility(invincibility)
{
  p_ChangeStride();
}


void OiramAnimation::Run()
{
  static uint8_t stride_delay = 3;
  
  stride_delay--;
  
  if (!stride_delay)
  {
    stride_delay = 3;
    p_ChangeStride();
  }
  
  m_GroundOffset += 2;
  
  if (m_GroundOffset == m_GroundSprite->width)
    m_GroundOffset = 0;
  
  return;
}


void OiramAnimation::Paint()
{
  static bool blink = false;
  
  gfx_SetColor(color_LT_BLUE);
  gfx_FillRectangle_NoClip(m_XPos, m_YPos, m_Width, m_Height);
  
  if (m_Invincibility)
    blink = !blink;
  else
    blink = false;
  
  if (!blink)
  {
    gfx_RLETSprite_NoClip(
      m_Sprite, m_XPos + (m_Width / 2), m_YPos + m_Height - m_Sprite->height - 16
    );
    
    if (m_Suit & FLAG_OIRAM_RACOON)
    {
      gfx_RLETSprite_NoClip(
        m_TailSprite,
        m_XPos + (m_Width / 2) - m_TailSprite->width + 1,
        m_YPos + m_Height - m_Sprite->height + 1
      );
    }
  }
  
  for (uint8_t i = 0; i < (LCD_WIDTH / m_GroundSprite->width) + 1; i++)
  {
    gfx_RLETSprite(
      m_GroundSprite,
      m_XPos - m_GroundOffset + (m_GroundSprite->width * i),
      m_YPos + m_Height - m_GroundSprite->height
    );
  }
  
  return;
}


void OiramAnimation::SetOiramSuit(const uint8_t suit)
{
  m_Suit = suit;
  
  if (m_Suit & FLAG_OIRAM_BIG)
  {
    if (m_Suit & FLAG_OIRAM_FIRE)
    {
      m_Sprite = oiram_0_fire;
      return;
    }
    
    if (m_Suit & FLAG_OIRAM_RACOON)
    {
      m_Sprite = oiram_0_racoon;
      return;
    }
    
    m_Sprite = oiram_0_big;
    return;
  }
  
  // Default to small suit
  m_Sprite = oiram_0_small;
  return;
}


void OiramAnimation::SetOiramInvincibility(const bool invincible)
{
  m_Invincibility = invincible;
  return;
}