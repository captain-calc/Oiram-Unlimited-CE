// Name:    Captain Calc
// Date:    August 11, 2021
// File:    horizlistmenu.h
// Purpose: This file declares the HorizListMenu class. This class is a
//          FocusableWidget that presents a horizontal text-based menu to the
//          user.


#ifndef HORIZLISTMENU_H
#define HORIZLISTMENU_H


#include <stdint.h>

#include "widgets.h"

#define HORIZLISTMENU_MAX_NUM_ITEMS  10


// Description: p_Paint() erases and re-paints the HorizListMenu.
// Pre:         All entries must fit onscreen.
// Post:        HorizListMenu painted.


// Description: HorizListMenu() (parameterized constructor) creates a
//              HorizListMenu instance.
// Pre:         <size> must be less than HORIZLISTMENU_MAX_NUM_ITEMS.
//              <index> must be less than <size>.
//              <x> should allow the entire list to fit onscreen.
//              <y> should allow the entire list to fit onscreen.
// Post:        New HorizListMenu instance created.
//              <index> set to 0 if <index> is greater than <size>.
//              List's cursor color set to unfocused cursor color.


// Description: Run() increments or decrements the list index if the user
//              presses the appropriate key.
// Pre:         None
// Post:        List index changed if valid key pressed. List cursor color set
//              to focused cursor color.


// Description: Paint() calls p_Paint().
// Pre:         None
// Post:        p_Paint() called.


// Description: UnfocusedPaint() sets the list cursor color to unfocused cursor
//              color and calls p_Paint().
// Pre:         None
// Post:        List cursor color set to unfocused cursor color and p_Paint
//              called.


// Description: GetOffset() retrieves the value of <m_Index>.
// Pre:         None
// Post:        <m_Index> returned.


// Description: ~HorizListMenu destroys a HorizListMenu instance.
// Pre:         None
// Post:        HorizListMenu instance destroyed.


class HorizListMenu : public FocusableWidget
{
  private:
    uint8_t     m_CursorColor;
    uint8_t     m_Index;
    uint8_t     m_Size;
    uint24_t    m_XPos;
    uint8_t     m_YPos;
    const char *m_Items[HORIZLISTMENU_MAX_NUM_ITEMS];
  
    void p_Paint();
  
  public:
    HorizListMenu(
      const char *items[],
      const uint8_t size,
      const uint8_t index,
      const uint24_t x,
      const uint8_t y
    );
    
    void Run();
    void Paint();
    void UnfocusedPaint();
    
    uint8_t GetOffset() { return m_Index; }
    
    ~HorizListMenu() {}
};

#endif