// Name:    Captain Calc
// Date:    August 11, 2021
// File:    gfxclass.h
// Purpose: gfxclass defines a class that encapsulates the setup and teardown
//          of GraphX.

// This code was based on DrDnar's GraphX class for the Programmer's Calculator.


#ifndef GFXCLASS_H
#define GFXCLASS_H


// Description: p_Begin() starts the 8bpp graphics and sets the palette, GraphX
//              transparent color, and draw location.
// Pre:         None
// Post:        8bpp graphics initialized and <m_Active> set.


// Description: GraphX() (parameterized constructor) creates a new GraphX
//              instance.
// Pre:         <palette> should be a GraphX palette.
//              <size> must be the size of the palette.
//              <offset> must be the offset into the palette table.
//              <transparent_color> will be GraphX's transparent color index.
// Post:        New GraphX class instance created. LCD set up to use GraphX if
//              there is no extant instance of the GraphX class.


// Description: Begin() calls p_Begin() if a GraphX instance exists.
// Pre:         None
// Post:        p_Begin() called if GraphX instance exists.


// Description: End() resets the LCD to OS defaults if a GraphX instance
//              exists.
// Pre:         None
// Post:        LCD reset to OS defaults if GraphX instance exists.


// Description: IsActive() retrieves the value of <m_Active>.
// Pre:         None
// Post:        <m_Active> returned.


// Description: ~GraphX() destroys a GraphX class instance.
// Pre:         None
// Post:        GraphX class instance destroyed. LCD reset to OS defaults.


class GraphX
{
  private:
    static GraphX* instance;
    void           p_Begin();
    
    static bool    m_Active;
    const void*    m_Palette;
    size_t         m_Size;
    uint8_t        m_Offset;
    uint8_t        m_TransparentColor;
    
  public:
    GraphX(
      const void* palette,
      size_t size,
      uint8_t offset,
      uint8_t transparent_color
    );
    
    static void Begin();
    static void End();
    static bool IsActive() { return m_Active; }
    
    ~GraphX();
};

#endif