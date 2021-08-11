// Name:    Captain Calc
// Date:    August 10, 2021
// File:    timer.h
// Purpose: This file declares the Timer class. This class encapsulates the
//          first hardware timer and is used to time cursor blinking.


#ifndef TIMER_H
#define TIMER_H


// Description: Timer() (default constructor) creates a new Timer instance and
//              automatically calls Reset().
// Pre:         None
// Post:        New Timer instance created.


// Description: ~Timer() disables the hardware timer and destroys the Timer
//              instance.
// Pre:         None
// Post:        Timer instance destroyed.


// Description: Reset() reloads the timer and sets it to expire every half
//              second.
// Pre:         None
// Post:        First hardware timer reloaded.


// Description: IsExpired() determines if the timer has expired and calls
//              Reset() if it has.
// Pre:         None
// Post:        If timer expired, Reset() called and true returned. False
//              returned otherwise.


class Timer
{
  private:
    static const unsigned int m_CyclesPerSecond = 32768;
    static Timer instance;
    
    Timer();
    ~Timer();
    
  public:
    static void Reset();
    static bool IsExpired();
};

#endif