// Name:    Captain Calc
// Date:    August 11, 2021
// File:    oiramanimation.h
// Purpose: This file declares the OiramAnimation class. This class can be
//          added to a GUI class as an UnfocusableWidget.


#ifndef OIRAMANIMATION_H
#define OIRAMANIMATION_H


#include <stdint.h>

#include <graphx.h>

#include "widgets.h"


// Description: p_ChangeStride() changes the sprite pointed to by <m_Sprite>
//              to simulate walking. Defaults to small Oiram suit if no other
//              matches are found.
// Pre:         None
// Post:        <m_Sprite> changed to next sprite in walking animation.


// Description: OiramAnimation() (parameterized constructor) creates a new
//              OiramAnimation instance.
// Pre:         <x>, <y>, <width>, and <height> should make the entire
//              animation fit onscreen.
//              <suit> must be a pointer to a valid Oiram sprite.
// Post:        OiramAnimation instance created.  <m_GroundOffset> initialized
//              to zero. <m_TailSprite> and <m_GroundSprite> set.


// Description: Run() switches Oiram sprites and alters <m_GroundOffset> to
//              simulate Oiram walking.
// Pre:         None
// Post:        <m_Sprite> and <m_GroundOffset> altered.


// Description: Paint() paints the current state of the animation. It paints
//              the racoon tail if necessary.
// Pre:         None
// Post:        Current state of animation painted.


// Description: SetOiramSuit() sets <m_Suit> to <suit> and updates <m_Sprite>
//              to reflect the change. <m_Sprite> defaults to small Oiram suit
//              if necessary.
// Pre:         <suit> should be the Oiram "flags" byte.
// Post:        <m_Suit> set to <suit> and <m_Sprite> changed to appropriate
//              sprite.


// Description: SetOiramInvincibility() sets <m_Invincibility> to <invincible>.
// Pre:         None
// Post:        <m_Invincibility> set to <invincible>.


// Description: ~OiramAnimation() destroys an OiramAnimation instance.
// Pre:         None
// Post:        OiramAnimation instance destroyed.


class OiramAnimation : public UnfocusableWidget
{
  private:
    gfx_rletsprite_t *m_Sprite;
    gfx_rletsprite_t *m_TailSprite;
    gfx_rletsprite_t *m_GroundSprite;
    uint8_t m_GroundOffset;
    uint24_t m_XPos;
    uint8_t m_YPos;
    uint24_t m_Width;
    uint8_t m_Height;
    uint8_t m_Suit;
    bool m_Invincibility;
    
    void p_ChangeStride();
    
  public:
    OiramAnimation(
      const uint24_t x,
      const uint8_t y,
      const uint24_t width,
      const uint8_t height,
      const uint8_t suit,
      const bool invincibility
    );
    
    void Run();
    void Paint();
    void SetOiramSuit(const uint8_t suit);
    void SetOiramInvincibility(const bool invincible);
    
    virtual ~OiramAnimation() {}
};

#endif