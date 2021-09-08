// Name:    Captain Calc
// Date:    August 11, 2021
// File:    inputbuffer.h
// Purpose: This file declares the InputBuffer class. This class provides a
//          character buffer and routines for manipulating the buffer such as
//          character addition/deletion.


#ifndef INPUTBUFFER_H
#define INPUTBUFFER_H


#include <stdint.h>


// The input buffer is <m_Size> bytes long. The last byte is the NULL
// terminator which makes the buffer easy to print. This means that you only
// have <m_Size> - 1 bytes of memory to store characters.


// Description: InputBuffer() (parameterized constructor) creates a new
//              InputBuffer instance.
// Pre:         None
// Post:        InputBuffer instance created, <m_Buffer> allocated (and
//              initialized), and <m_WriteOffset> set to zero.


// Description: AddChar() adds a character to <m_Buffer>.
// Pre:         <m_WriteOffset> must be less than <m_Size> - 1.
// Post:        If successful, <c> added to <m_Buffer>, <m_WriteOffset>
//              incremented, and true returned. False returned otherwise.


// Description: RemoveChar() removes the last character from <m_Buffer>.
// Pre:         <m_WriteOffset> must be greater than zero.
// Post:        If successful, character removed, <m_WriteOffset> decremented,
//              and character returned. NULL returned otherwise.


// Description: EmptyBuffer() removes all characters from <m_Buffer>.
// Pre:         None
// Post:        All characters removed from buffer.


// Description: ForceSetBufferTo() empties <m_Buffer> and sets it to
//              <new_buffer>.
// Pre:         Length of <new_buffer> should be less than <m_Size> - 1. Any
//              bytes beyond this length will be truncated.
// Post:        <m_Buffer> emptied and set to <new_buffer>.


// Description: GetBuffer() returns a pointer to <m_Buffer>.
// Pre:         None
// Post:        Pointer to <m_Buffer> returned.


// Description: GetSize() retrieves the value of <m_Size>.
// Pre:         None
// Post:        <m_Size> returned.


// Description: ~InputBuffer() destroys an InputBuffer instance.
// Pre:         <m_Buffer> should point to allocated memory.
// Post:        InputBuffer instance destroyed and <m_Buffer> freed.


class InputBuffer
{
  private:
    char *  m_Buffer;
    size_t  m_Size;
    uint8_t m_WriteOffset;
  
  public:
    InputBuffer(const size_t size);
    
    virtual bool AddChar(const char c);
    virtual char RemoveChar();
    virtual void EmptyBuffer();
    virtual void ForceSetBufferTo(const char new_buffer[]);
    
    char *GetBuffer() const { return m_Buffer; }
    size_t GetSize() const { return m_Size; }
    
    ~InputBuffer() { delete [] m_Buffer; }
};


#endif