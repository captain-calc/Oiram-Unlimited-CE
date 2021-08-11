// Name:    Captain Calc
// Date:    August 11, 2021
// File:    numericalinput.h
// Purpose: This file declares the NumericalInput class. This class is an
//          InputBuffer that only accepts numbers and can be added to a GUI
//          class as a FocusableWidget.


#ifndef NUMERICALINPUT_H
#define NUMERICALINPUT_H

#include <stdint.h>

#include <tice.h>

#include "inputbuffer.h" 
#include "widgets.h"


// Globals for easily setting up a NumericalInput instance with a range from
// zero to 999.
#define NUMERICAL_INPUT_STD_FIELD_WIDTH     ((uint24_t)100)
#define NUMERICAL_INPUT_STD_FIELD_HEIGHT    ((uint8_t)13)
#define NUMERICAL_INPUT_STD_BUFFER_SIZE     ((size_t)4)
#define NUMERICAL_INPUT_CURSOR_COLOR        color_BLACK
#define NUMERICAL_INPUT_FIELD_BORDER_COLOR  color_BLACK
#define NUMERICAL_INPUT_FIELD_BG_COLOR      color_WHITE


// Description: p_InitFieldCoords() initializes the <m_Buffer*> and <m_Cursor*>
//              variables, placing the cursor at the field's far left.
// Pre:         None
// Post:        <m_Buffer*> and <m_Cursor*> variables initialized.


// Description: p_Paint() paints the numerical input field WITHOUT checking the
//              timer to decide whether or not to draw the cursor.
// Pre:         None
// Post:        Widget painted.


// Description: NumericalInput() (two-parameter constructor) creates a new
//              NumericalInput instance defaulting to the standard values
//              of <m_Width> and <m_Height> (see globals above). It also
//              creates the InputBuffer subobject with the standard size.
// Pre:         <x> and <y> must be values that allow the field to fit
//              onscreen.
// Post:        New NumericalInput instance created.
//              <m_MinValue> initialized to zero.
//              <m_MaxValue> initialized to 999.


// Description: NumericalInput() (five-parameter constructor) creates a new
//              NumericalInput instance.
// Pre:         <size> must be small enough that the field text does not
//              overflow the field. <x>, <y>, <width>, and <height> must be
//              values that allow the field to fit onscreen.
// Post:        New NumericalInput instance created.
//              <m_MinValue> initialized to zero.
//              <m_MaxValue> initialized to 999.


// Description: AddChar() adds <c> to the InputBuffer subobject's <m_Buffer>
//              if there is room for it.
// Pre:         <c> should be a numeral.
// Post:        If <c> is successfully added, <m_CursorXPos> is updated and
//              true returned. False returned otherwise.


// Description: RemoveChar() removes the last numeral from the InputBuffer
//              subobject's <m_Buffer> if any.
// Pre:         None
// Post:        If successful, the removed character is returned and
//              <m_CursorXPos> is updated. NULL returned otherwise.


// Description: EmptyBuffer() empties the InputBuffer subobject's <m_Buffer>.
// Pre:         None
// Post:        InputBuffer subobject's <m_Buffer> emptied.


// Description: ForceSetNumberTo() sets the InputBuffer subobject's <m_Buffer>
//              to <value>.
// Pre:         Length of <value>'s string representation should be less than
//              the subobject's <m_Size>.
// Post:        InputBuffer subobject's <m_Buffer> set to <value>.


// Description: KeyToNumeral() converts <key> to a numeral character.
// Pre:         None
// Post:        If <key> corresponds to a number, true returned and <numeral>
//              set to corresponding character. False returned otherwise.


// Description: Run() gets a key from the user and adds/removes characters from
//              the InputBuffer subobject if necessary. If the final value
//              exceeds either of the NumericalInput's value bounds, the buffer
//              is set to the exceeded value.
// Pre:         <m_MinValue> must be less than <m_MaxValue>.
// Post:        User queried for keypress and characters added or removed from
//              the InputBuffer subobject based on the keypress.


// Description: Paint() (re)sets <m_Blink> based on whether the Timer has
//              expired and calls p_Paint().
// Pre:         None
// Post:        Widget painted.


// Description: UnfocusedPaint() sets <m_Blink> to true and calls p_Paint().
// Pre:         None
// Post:        Widget painted without cursor.


// Description: SetMinValue() sets the minimum boundary that the input buffer
//              cannot exceed (<m_MinValue> = <min>).
// Pre:         <min> must be less than <m_MaxValue>.
// Post:        If successful, true returned. False returned otherwise.


// Description: SetMaxValue() sets the upper boundary that the input buffer
//              cannot exceed (<m_MaxValue> = <max>).
// Pre:         <max> must be greater than <m_MinValue>.
// Post:        If successful, true returned. False returned otherwise.


// Description: GetValue() calculates the numerical value of the InputBuffer
//              subobject's <m_Buffer>.
// Pre:         None
// Post:        Numerical value of <m_Buffer> returned.


// Description: IsValidValue() determines if the numerical value of the
//              InputBuffer subobject's <m_Buffer> is within the NumericalInput
//              bounds.
// Pre:         <m_MinValue> must be less than <m_MaxValue>.
// Post:        If within bounds, true returned. False returned otherwise.


// Description: ~NumericalInput() destroys a NumericalInput instance.
// Pre:         None
// Post:        NumericalInput instance destroyed.


class NumericalInput : public InputBuffer, public FocusableWidget
{
  private:
    uint24_t m_XPos;
    uint8_t  m_YPos;
    uint24_t m_FieldWidth;
    uint8_t  m_FieldHeight;
    uint24_t m_BufferXPos;
    uint8_t  m_BufferYPos;
    uint24_t m_CursorXPos;
    uint8_t  m_CursorYPos;
    uint8_t  m_CursorWidth;
    uint8_t  m_CursorHeight;
    long     m_MinValue;
    long     m_MaxValue;
    bool     m_Blink;
    
    void p_InitFieldCoords();
    void p_Paint();
  
  public:
    NumericalInput(const uint24_t x, const uint8_t y);
    NumericalInput(
      const uint8_t size,
      const uint24_t x,
      const uint8_t y,
      const uint24_t width,
      const uint8_t height
    );
    
    bool AddChar(const char c);
    char RemoveChar();
    void EmptyBuffer();
    void ForceSetNumberTo(const long value);
    
    bool KeyToNumeral(const sk_key_t key, char *numeral) const;
    void Run();
    void Paint();
    void UnfocusedPaint();
    
    bool SetMinValue(const long min);
    bool SetMaxValue(const long max);
    long GetValue() { return atol(GetBuffer()); }
    bool IsValidValue();
    
    virtual ~NumericalInput() {}
};

#endif