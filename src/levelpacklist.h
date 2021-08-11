// Name:    Captain Calc
// Date:    August 11, 2021
// File:    levelpacklist.h
// Purpose: levelpacklist provides a class that encapsulates the list of Oiram
//          level packs on the calculator. It may be added to a GUI class as a
//          FocusableWidget.


#ifndef LEVELPACKLIST_H
#define LEVELPACKLIST_H


#include <tice.h>

#include "widgets.h"


#define MAX_NUM_PACKS  ((uint8_t)255)


// m_NumPacks should be an uint8_t, see src/loadscreen.h


// Description: LevelPackList() constructs a new LevelPackList instance with a
//              fresh list of level packs.
// Pre:         None
// Post:        New LevelPackList instance returned.


// Description: Update() refreshes the instance's level pack list.
//              Note: Only level packs listed in the calculator's VAT are
//              recorded. Packs on external USB drives are not included.
// Pre:         None
// Post:        Instance's level pack list contains all Oiram level packs that
//              are available.


// Description: GetNumPacks() returns the number of packs in the list.
// Pre:         None
// Post:        Number of packs returned.


// Description: GetPackName() returns the name of the appvar at the given list
//              index.
// Pre:         <i> should be greater than zero.
// Post:        For a valid index, the appvar's name is returned. For an
//              invalid index, NULL is returned.


// Description: GetCurrPackName() returns the name of the appvar at <m_Index>
//              in the list.
// Pre:         <m_Index> must be less than <m_NumPacks>.
// Post:        Appvar name returned.


// Description: ~LevelPackList() destroys a LevelPackList instance.
// Pre:         <m_PackNames> must contain valid pointers to allocated memory.
// Post:        LevelPackList instance destroyed. <m_PackNames> pointers freed.


class LevelPackList : public FocusableWidget
{
  private:
    static const uint8_t m_WIDTH = 100;
    static const uint8_t m_HEIGHT = 20;
    static const uint8_t m_XPOS = (LCD_WIDTH / 2) - (m_WIDTH / 2);
    static const uint8_t m_YPOS = 120;
    
    uint8_t m_Index;
    uint8_t m_NumPacks;
    char *  m_PackNames[MAX_NUM_PACKS];
  
  public:
    LevelPackList(): m_Index(0) { Update(); }
    
    void Update();
    void Run();
    void Paint();
    void UnfocusedPaint() {}
    
    uint8_t GetNumPacks() const { return m_NumPacks; }
    char *GetPackName(const uint8_t i) const;
    char *GetCurrPackName() { return m_PackNames[m_Index]; }
    
    ~LevelPackList();
};

#endif