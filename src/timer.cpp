// Name:    Captain Calc
// Date:    August 10, 2021
// File:    timer.cpp
// Purpose: This file provides the definitions of the Timer class member
//          functions declared in timer.h and sets up a Timer singleton.


#include "timer.h"

#include <tice.h>


// Initialize the Timer singleton.
Timer Timer::instance;


Timer::Timer()
{
  Reset();
}


Timer::~Timer()
{
  timer_Disable(1);
}


void Timer::Reset()
{
  timer_Disable(1);
  timer_Set(1, m_CyclesPerSecond / 2);
  timer_SetReload(1, m_CyclesPerSecond / 2);
  timer_Enable(1, TIMER_32K, TIMER_0INT, TIMER_DOWN);
}


bool Timer::IsExpired()
{
  bool expired = false;
  
  if (timer_ChkInterrupt(1, TIMER_RELOADED))
  {
    timer_AckInterrupt(1, TIMER_RELOADED);
    Reset();
    expired = true;
  }
  
  return expired;
}
