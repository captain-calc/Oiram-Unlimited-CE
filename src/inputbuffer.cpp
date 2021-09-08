// Name:    Captain Calc
// Date:    August 10, 2021
// File:    inputbuffer.cpp
// Purpose: This file provides the definitions of the InputBuffer class member
//          functions declared in inputbuffer.h.


#include <stdint.h>
#include <string.h>

#include "inputbuffer.h"


InputBuffer::InputBuffer(const size_t size): m_Size(size), m_WriteOffset(0)
{
  m_Buffer = new char[size];
  memset(m_Buffer, '\0', size);
}


bool InputBuffer::AddChar(const char c)
{
  bool added = false;
  
  if (m_WriteOffset < m_Size - 1)
  {
    m_Buffer[m_WriteOffset++] = c;
    added = true;
  }
  
  return added;
}


char InputBuffer::RemoveChar()
{
  char removed = '\0';
  
  if (m_WriteOffset)
  {
    removed = m_Buffer[--m_WriteOffset];
    m_Buffer[m_WriteOffset] = '\0';
  }
  
  return removed;
}


void InputBuffer::EmptyBuffer()
{
  while (RemoveChar());
  return;
}


void InputBuffer::ForceSetBufferTo(const char new_buffer[])
{
  EmptyBuffer();
  strncpy(m_Buffer, new_buffer, m_Size - 1);
  m_WriteOffset = strlen(new_buffer);
  return;
}