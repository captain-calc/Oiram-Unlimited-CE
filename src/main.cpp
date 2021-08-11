// Name:    Captain Calc
// Date:    August 9, 2021
// File:    main.cpp
// Purpose: This file provides the main control loop of the program.


// PROGRAM SPECIFICATIONS
//
// Step 1: Load available level packs.
//      The program should do a VAT search to find all of the Oiram level
//      packs. If a level pack is deleted, the Oiram save appvar will still
//      have the configuration for that level until the Oiram program is run
//      after the deletion.
//
// Step 2: Get desired level pack name from user.
//      The program will present a list of available level packs to the user
//      and get the desired pack using a menu-based interface.
//
// Step 3: Extract the level pack configuration from the Oiram save appvar.
//      This means opening the Oiram save appvar, locating the level pack
//      name within it, and extracting the associated configuration data.
//
// Step 4: Get the desired configuration alterations from the user.
//      The program will present a combination of numerical input fields and
//      toggles to the user.
//
// Step 5: Save the changes
//      Open the Oiram save appvar and write the desired changes to the level
//      pack configuration.
//
// Step 6: Return to the level pack menu
//      Return to the main menu in case the user wishes to edit another level
//      pack.
//


// CLASS CONSTRUCTOR PRECONDITIONS NOTE
//
//     If the preconditions of a class constructor are not met, none of the
// member functions are guaranteed to work properly. If a member function
// has "None" as a precondition, it is still expected that the class is
// correctly setup.
//


#include <stdint.h>
#include <stdlib.h>

#include <fileioc.h>
#include <graphx.h>

#include "colors.h"
#include "gfxclass.h"
#include "gfx/gfx.h"
#include "mainfuncs.h"


// Setup the GraphX singleton to use the mainprog_palette.
GraphX graphx(mainprog_palette, sizeof_mainprog_palette, 0, color_WHITE);


int main()
{
  bool exit_menu = false;
  char *pack_name;
  
  // Close any open slots.
  ti_CloseAll();
  
  if (mainfuncs_OiramSaveAppvarExists())
  {
    do
    {
      pack_name = mainfuncs_GetPackName(&exit_menu);
    
      if (!exit_menu)
        mainfuncs_EditPack(pack_name);
    
    } while (!exit_menu);
  }
  else
  {
    mainfuncs_OiramSaveAppvarError();
  }
  
  return 0;
}
