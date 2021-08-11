// Name:    Captain Calc
// Date:    August 11, 2021
// File:    widgets.h
// Purpose: This file declares the UnfocusableWidget and FocusableWidget
//          classes.


#ifndef WIDGETS_H
#define WIDGETS_H


// NOTE: In every case a Paint() function only draws the graphical
// representation of a class. It does not copy (blit) the drawing to the screen
// if the drawing is written to the GraphX buffer.


// The UnfocusableWidget can be added to a GUI class but cannot be "focused" on,
// a.k.a, interacted with by the user. It has an IsAlive() function, a Run()
// function, and a Paint() function.
//     The GUI class uses the IsAlive() function to determine if the widget
// should automatically be removed (e.g. an UnfocusableWidget is an animation
// that has just finished and should be removed).
//     The Run() function allows the widget to run code that might alter its
// Paint() function (see oiramanimation.h).
//     The Paint() function paints the widget.


class UnfocusableWidget
{
  private:
    bool m_Alive;
    
  public:
    UnfocusableWidget(): m_Alive(false) {}
    
    bool IsAlive() const { return m_Alive; }
    virtual void Run() = 0;
    virtual void Paint() = 0;
    
    virtual ~UnfocusableWidget() = default;
};


// Like the UnfocusableWidget, the FocusableWidget can be added to a GUI class.
// It possess a "focus" which means if the widget is "focused" on by the GUI
// class, the user may interact with it. It has a Run() function, a Paint()
// function, and an UnfocusedPaint().
//     The Run() function must be executed in order for the user to interact
// with the widget. It allows the widget to update its private variables based
// on user input.
//     The Paint() function paints the widget.
//     The UnfocusedPaint() function is called each time the GUI switches focus
// from one widget to another. It leaves the widget in a graphically "pretty"
// state. For instance, the NumericalInput class uses this function to erase
// the cursor when the user leaves a widget of that class.


class FocusableWidget
{
  public:
    FocusableWidget() {}
    
    virtual void Run() = 0;
    virtual void Paint() = 0;
    virtual void UnfocusedPaint() = 0;
    
    virtual ~FocusableWidget() = default;
};


#endif