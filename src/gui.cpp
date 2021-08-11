// Name:    Captain Calc
// Date:    August 10, 2021
// File:    gui.cpp
// Purpose: This file provides the definitions of the GUI class member
//          functions declared in gui.h and sets up the GUI singleton.


#include <stdint.h>

#include "ccdbg.h"
#include "colors.h"
#include "gui.h"


// Setup the GUI singleton. The default GUI background color is black.
GUI GUI::instance;


UnfocusableWidget *GUI::m_UnfocusableWidgets[
  GUI::m_MAX_NUM_UNFOCUSABLE_WIDGETS
] = {
  nullptr, nullptr, nullptr
};

FocusableWidget *GUI::m_FocusableWidgets[
GUI::m_MAX_NUM_FOCUSABLE_WIDGETS] = {
  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr
};

uint8_t GUI::m_NumUnfocusableWidgets(0);
uint8_t GUI::m_NumFocusableWidgets(0);
uint8_t GUI::m_LastFocus(0);
uint8_t GUI::m_Focus(0);
uint8_t GUI::m_Background(color_BLACK);


bool GUI::AddUnfocusableWidget(UnfocusableWidget * widget)
{
  bool added = false;
  
  if (m_NumUnfocusableWidgets < m_MAX_NUM_UNFOCUSABLE_WIDGETS)
  {
    m_UnfocusableWidgets[m_NumUnfocusableWidgets++] = widget;
    added = true;
  }
  
  return added;
}


bool GUI::AddFocusableWidget(FocusableWidget * widget)
{
  bool added = false;
  
  if (m_NumFocusableWidgets < m_MAX_NUM_FOCUSABLE_WIDGETS)
  {
    m_FocusableWidgets[m_NumFocusableWidgets++] = widget;
    added = true;
  }
  
  return added;
}


void GUI::RemoveUnfocusableWidget(const uint8_t index)
{
  uint8_t i;
  
  // If m_NumUnfocusableWidgets == 0, this will not execute regardless of the
  // value of <index>.
  if (index < m_NumUnfocusableWidgets)
  {
    m_UnfocusableWidgets[index] = nullptr;
    m_NumUnfocusableWidgets--;
    
    i = index;
  
    while (i < m_NumUnfocusableWidgets)
    {
      m_UnfocusableWidgets[i - 1] = m_UnfocusableWidgets[i];
      i++;
    }
  }
  
  return;
}


void GUI::RemoveFocusableWidget(const uint8_t index)
{
  uint8_t i;
  
  // If m_NumFocusableWidgets == 0, this will not execute regardless of the
  // value of <index>.
  if (index < m_NumFocusableWidgets)
  {
    m_FocusableWidgets[index] = nullptr;
    m_NumFocusableWidgets--;
    
    i = index;
  
    while (i < m_NumFocusableWidgets)
    {
      m_FocusableWidgets[i - 1] = m_FocusableWidgets[i];
      i++;
    }
  }
  
  return;
}


void GUI::RemoveAllUnfocusableWidgets()
{
  for (uint8_t i = 0; i < m_NumUnfocusableWidgets; i++)
    m_UnfocusableWidgets[i] = nullptr;
  
  m_NumUnfocusableWidgets = 0;
  return;
}


void GUI::RemoveAllFocusableWidgets()
{
  for (uint8_t i = 0; i < m_NumFocusableWidgets; i++)
    m_FocusableWidgets[i] = nullptr;
  
  m_NumFocusableWidgets = 0;
  m_LastFocus = 0;
  m_Focus = 0;
  return;
}


void GUI::RunAllUnfocusableWidgets()
{
  for (uint8_t i = 0; i < m_NumUnfocusableWidgets; i++)
  {
    m_UnfocusableWidgets[i]->Run();
    
    // Unfocusable widgets should ensure that their last paint is executed before
    // reseting m_Alive.
    if (!(m_UnfocusableWidgets[i]->IsAlive()))
      RemoveUnfocusableWidget(i);
  }
  
  return;
}


bool GUI::RunUnfocusableWidget(const uint8_t index)
{
  bool run = false;
  
  if (index < m_NumUnfocusableWidgets)
  {
    m_UnfocusableWidgets[index]->Run();
    run = true;
  }
  
  return run;
}


void GUI::RunFocusedWidget()
{
  m_FocusableWidgets[m_Focus]->Run();
  return;
}


void GUI::PaintAllUnfocusableWidgets()
{
  for (uint8_t i = 0; i < m_NumUnfocusableWidgets; i++)
    m_UnfocusableWidgets[i]->Paint();
  
  return;
}


bool GUI::PaintUnfocusableWidget(const uint8_t index)
{
  bool painted = false;
  
  if (index < m_NumUnfocusableWidgets)
  {
    m_UnfocusableWidgets[index]->Paint();
    painted = true;
  }
  
  return painted;
}


void GUI::PaintAllFocusableWidgets()
{
  for (uint8_t i = 0; i < m_NumFocusableWidgets; i++)
    m_FocusableWidgets[i]->Paint();
  
  return;
}


void GUI::PaintFocusedWidget()
{
  // Paint the widget that last had focus if the focus changed since the last
  // paint. This erases any unwanted artifacts like a cursor caret.
  if (m_LastFocus != m_Focus)
  {
    m_FocusableWidgets[m_LastFocus]->UnfocusedPaint();
    m_LastFocus = m_Focus;
  }
  
  // Paint the widget that has focus.
  m_FocusableWidgets[m_Focus]->Paint();
  return;
}


bool GUI::SetFocus(const uint8_t focus)
{
  bool focus_set = false;
  
  if (focus < m_NumFocusableWidgets)
  {
    m_Focus = focus;
    focus_set = true;
  }
  
  return focus_set;
}


bool GUI::MoveFocusBack()
{
  bool focus_moved = false;
  
  if (m_Focus)
  {
    m_Focus--;
    focus_moved = true;
  }
  
  return focus_moved;
}


bool GUI::MoveFocusForward()
{
  // Note that we are not using "m_Focus++" which would increment the variable
  // without validating that it can be incremented.
  return SetFocus(m_Focus + 1);
}
