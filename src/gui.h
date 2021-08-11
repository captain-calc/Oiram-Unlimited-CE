// Name:    Captain Calc
// Date:    August 11, 2021
// File:    gui.h
// Purpose: This file declares the GUI class. This class controls the drawing
//          and execution of any FocusableWidget or UnfocusableWidget added to
//          it.


#ifndef GUI_H
#define GUI_H


#include <stdint.h>

#include "widgets.h"


// Description: GUI() (default constructor) creates a new GUI instance.
// Pre:         None
// Post:        New GUI instance created.


// Description: ~GUI() destroys a GUI instance.
// Pre:         None
// Post:        GUI instance destroyed.


// Description: AddUnfocusableWidget() adds an UnfocusableWidget to the member
//              list of UnfocusableWidget's.
// Pre:         <m_NumUnfocusableWidgets> must be less than
//              m_MAX_NUM_UNFOCUSABLE_WIDGETS.
// Post:        If successful, widget added and true returned. False returned
//              otherwise.


// Description: AddFocusableWidget() adds a FocusableWidget to the member list
//              of FocusableWidget's.
// Pre:         <m_NumFocusableWidgets> must be less than
//              m_MAX_NUM_FOCUSABLE_WIDGETS.
// Post:        If successful, widget added and true returned. False returned
//              otherwise.


// Description: RemoveUnfocusableWidget() removes the UnfocusableWidget at
//              <index> from <m_UnfocusableWidgets>.
// Pre:         <index> must be less than <m_NumUnfocusableWidgets>.
// Post:        Widget removed. If removal leaves a gap in the list, all of the
//              widget pointers to the right of <index> are shifted left.


// Description: RemoveFocusableWidget() removes the FocusableWidget at <index>
//              from <m_FocusableWidgets>.
// Pre:         <index> must be less than <m_NumFocusableWidgets>.
// Post:        Widget removed. If removal leaves a gap in the list, all of the
//              widget pointers to the right of <index> are shifted left.


// Description: RemoveAllUnfocusableWidgets() removes all widgets from
//              <m_UnfocusableWidgets>.
// Pre:         None
// Post:        All entries in <m_UnfocusableWidgets> set to nullptr and
//              <m_NumUnfocusableWidgets> set to zero.


// Description: RemoveAllFocusableWidgets() removes all widgets from
//              <m_FocusableWidgets>.
// Pre:         None
// Post:        All entries in <m_FocusableWidgets> set to nullptr and
//              <m_NumFocusableWidgets> set to zero.


// Description: RunAllUnfocusableWidgets() executes the Run() function of all
//              of the widgets in <m_UnfocusableWidgets> and removes any "dead"
//              widgets.
// Pre:         None
// Post:        Run() function of all widgets in <m_UnfocusableWidgets>
//              executed and any "dead" UnfocusableWidget's are removed from
//              <m_UnfocusableWidgets>.


// Description: RunUnfocusableWidget() executes the Run() function of the
//              widget at <index> in <m_UnfocusableWidgets>.
// Pre:         <index> must be less than <m_NumUnfocusableWidgets>.
// Post:        If successful, Run() function of <m_UnfocusableWidgets[index]>
//              executed and true returned. False returned otherwise.


// Description: RunFocusedWidget() executes the focused widget's Run()
//              function.
// Pre:         The GUI must have at least one FocusableWidget and the
//              m_Focus must be the index of a FocusableWidget. In other
//              words, this function will result in undefined behavior if
//              there are no FocusableWidget's in the GUI.
// Post:        Run() function of focused widget executed.


// Description: PaintAllUnfocusableWidgets() executes the Paint() function of
//              all widgets in <m_UnfocusableWidgets>.
// Pre:         None
// Post:        Paint() function of all widgets in <m_UnfocusableWidgets>
//              executed.


// Description: PaintUnfocusableWidget() executes the Paint() function of the
//              widget at <index> in <m_UnfocusableWidgets>.
// Pre:         <index> must be less than <m_NumUnfocusableWidgets>.
// Post:        If successful, Paint() function of
//              <m_UnfocusableWidgets[index]> executed and true returned. False
//              returned otherwise.


// Description: PaintAllFocusableWidgets() executes the Paint() function of all
//              widgets in <m_FocusableWidgets>.
// Pre:         None
// Post:        Paint() function of all widgets in <m_FocusableWidgets>
//              executed.


// Description: PaintFocusedWidget() paints the widget that has focus and
//              executes the UnfocusedPaint() on the last widget that had
//              focus if necessary.
// Pre:         The GUI must have at least one FocusableWidget and the
//              m_Focus must be the index of a FocusableWidget. In other
//              words, this function will result in undefined behavior if
//              there are no FocusableWidget's in the GUI.
// Post:        Widget that has focus painted and widget that last had focus
//              executes its UnfocusedPaint() if necessary.


// Description: SetFocus() sets <m_Focus> to <focus>.
// Pre:         <focus> must be less than <m_NumFocusableWidgets>.
// Post:        If successful, <m_Focus> set to <focus> and true returned.
//              False returned otherwise.


// Description: MoveFocusBack() decrements <m_Focus>.
// Pre:         <m_Focus> must be greater than zero.
// Post:        If successful, <m_Focus> decremented and true returned. False
//              returned otherwise.


// Description: MoveFocusForward() increments <m_Focus>.
// Pre:         <m_Focus> must be less than <m_NumFocusableWidgets>.
// Post:        If successful, <m_Focus> incremented and true returned. False
//              returned otherwise.


// Description: SetBGColor() sets <m_Background> to <color>.
// Pre:         <color> should be a valid palette index.
// Post:        <m_Background> set to <color>.


// Description: GetBGColor() retrieves the value of <m_Background>.
// Pre:         None
// Post:        <m_Background> returned.


class GUI
{
  private:
    static const uint8_t m_MAX_NUM_UNFOCUSABLE_WIDGETS = 3;
    static const uint8_t m_MAX_NUM_FOCUSABLE_WIDGETS = 6;
    static GUI instance;
    
    GUI() {}
    ~GUI() {}
    
    static UnfocusableWidget *m_UnfocusableWidgets[m_MAX_NUM_UNFOCUSABLE_WIDGETS];
    static FocusableWidget *m_FocusableWidgets[m_MAX_NUM_FOCUSABLE_WIDGETS];
    static uint8_t m_NumUnfocusableWidgets;
    static uint8_t m_NumFocusableWidgets;
    static uint8_t m_LastFocus;
    static uint8_t m_Focus;
    static uint8_t m_Background;
  
  public:
    static bool AddUnfocusableWidget(UnfocusableWidget * widget);
    static bool AddFocusableWidget(FocusableWidget * widget);
    static void RemoveUnfocusableWidget(const uint8_t index);
    static void RemoveFocusableWidget(const uint8_t index);
    static void RemoveAllUnfocusableWidgets();
    static void RemoveAllFocusableWidgets();
    
    static void RunAllUnfocusableWidgets();
    static bool RunUnfocusableWidget(const uint8_t index);
    static void RunFocusedWidget();
    
    static void PaintAllUnfocusableWidgets();
    static bool PaintUnfocusableWidget(const uint8_t index);
    static void PaintAllFocusableWidgets();
    static void PaintFocusedWidget();
    
    static bool SetFocus(const uint8_t focus);
    static bool MoveFocusBack();
    static bool MoveFocusForward();
    
    static void SetBGColor(const uint8_t color) { m_Background = color; }
    static uint8_t GetBGColor() { return m_Background; }
};


#endif