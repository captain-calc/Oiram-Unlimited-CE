// Name:    Captain Calc
// Date:    August 11, 2021
// File:    mainfuncs.h
// Purpose: This file provides the MainMenuBackground and EditorBackground
//          classes as well as functions used by main.cpp.


#ifndef MAINFUNCS_H
#define MAINFUNCS_H


#include "widgets.h"


// Description: MainMenuBackground() (default constructor) creates a new
//              MainMenuBackground instance.
// Pre:         None
// Post:        MainMenuBackground instance created.


// Description: Run() is defined to satisfy the UnfocusableWidget inheritance
//              requirements but is not used.
// Pre:         None
// Post:        None


// Description: Paint() paints the MainMenuBackground.
// Pre:         None
// Post:        Background for main menu painted.


// Description: ~MainMenuBackground() destroys a MainMenuBackground instance.
// Pre:         None
// Post:        MainMenuBackground instance destroyed.


class MainMenuBackground : public UnfocusableWidget
{
  public:
    MainMenuBackground(): UnfocusableWidget() {}
    
    void Run() {}
    void Paint();
    
    virtual ~MainMenuBackground() {}
};


// Description: EditorBackground() (default constructor) creates a new
//              EditorBackground instance.
// Pre:         None
// Post:        EditorBackground instance created.


// Description: Run() is defined to satisfy the UnfocusableWidget inheritance
//              requirements but is not used.
// Pre:         None
// Post:        None


// Description: Paint() paints the EditorBackground.
// Pre:         None
// Post:        Background for level pack editor painted.


// Description: ~EditorBackground() destroys an EditorBackground instance.
// Pre:         None
// Post:        EditorBackground instance destroyed.


class EditorBackground : public UnfocusableWidget
{
  public:
    EditorBackground(): UnfocusableWidget() {}
    
    void Run() {}
    void Paint();
    
    virtual ~EditorBackground() {}
};


// Description: mainfuncs_OiramSaveAppvarExists() determines if the Oiram save
//              appvar exists.
// Pre:         None
// Post:        True returned if it exists. False returned otherwise.
bool mainfuncs_OiramSaveAppvarExists();


// Description: mainfuncs_GetPackName() controls the main menu.
// Pre:         Oiram save appvar must exist.
// Post:        Selected level pack name returned. <exit_menu> set if user
//              pressed the exit key.
char *mainfuncs_GetPackName(bool *exit_menu);


// Description: mainfuncs_EditPack() controls the level pack editor menu.
// Pre:         <name> must be the name of a non-password-protected Oiram level
//              pack. Oiram save appvar must exist and hold a save
//              configuration corresponding to <name>.
// Post:        Level pack edited and any changes to it written to the Oiram
//              save appvar.
void mainfuncs_EditPack(const char *name);


// Description: mainfuncs_PrintOiramSaveAppvarError() prints an error to the
//              screen stating that the Oiram save appvar does not exist and
//              waits for the user to press any key.
// Pre:         None
// Post:        Error printed to screen.
void mainfuncs_OiramSaveAppvarError();


#endif