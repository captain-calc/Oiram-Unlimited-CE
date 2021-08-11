// Name:    Captain Calc
// Date:    August 10, 2021
// File:    mainfuncs.cpp
// Purpose: This file provides the definitions of the functions declared in
//          mainfuncs.h and the member function definitions of both the
//          MainMenuBackground and the EditorBackground classes.



#include <string.h>  // For strncpy()

#include <graphx.h>
#include <keypadc.h>
#include <tice.h>

#include "ccdbg.h"
#include "asmutil.h"
#include "colors.h"
#include "cutil.h"
#include "gfx/gfx.h"
#include "gui.h"
#include "horizlistmenu.h"
#include "levelpack.h"
#include "levelpacklist.h"
#include "mainfuncs.h"
#include "numericalinput.h"
#include "oiramanimation.h"


void MainMenuBackground::Paint()
{
  const char *title[2] = {
    "OIRAM",
    "UNLIMITED"
  };
  
  gfx_FillScreen(GUI::GetBGColor());
  gfx_SetTextBGColor(GUI::GetBGColor());
  gfx_SetTextFGColor(color_WHITE);
  gfx_SetTextTransparentColor(GUI::GetBGColor());
  gfx_SetTextScale(2, 3);
  
  cutil_PrintCentered(title[0], 20);
  cutil_PrintCentered(title[1], 50);
  
  gfx_SetTextScale(1, 1);
  return;
}


void EditorBackground::Paint()
{
  gfx_FillScreen(GUI::GetBGColor());
  gfx_SetTextBGColor(GUI::GetBGColor());
  gfx_SetTextFGColor(color_WHITE);
  gfx_SetTextTransparentColor(GUI::GetBGColor());
  
  gfx_PrintStringXY("Level:", 2, 123);
  gfx_PrintStringXY("Coins:", 2, 143);
  gfx_PrintStringXY("Lives:", 2, 163);
  gfx_PrintStringXY("Invincibility:", 2, 182);
  gfx_PrintStringXY("Suit:", 2, 202);
  gfx_PrintStringXY("Score:", 2, 223);
  return;
}


bool mainfuncs_OiramSaveAppvarExists()
{
  bool extant = false;
  ti_var_t slot; 
  
  if ((slot = ti_Open(OIRAM_SAVE_APPVAR, "r")))
  {
    extant = true;
    ti_Close(slot);
  }
  
  return extant;
}


char *mainfuncs_GetPackName(bool *exit_menu)
{
  static char pack_name[PACK_NAME_LEN] = {'\0'};
  bool exit = false;
  bool name_selected = false;
  sk_key_t key;
  
  MainMenuBackground mmbg;
  GUI::AddUnfocusableWidget(&mmbg);
  
  LevelPackList pack_list;
  GUI::AddFocusableWidget(&pack_list);
  
  GUI::PaintAllUnfocusableWidgets();
  GUI::PaintAllFocusableWidgets();
  
  do
  {
    delay(100);
    
    kb_Scan();
    key = asm_GetCSC();
    GUI::RunFocusedWidget();
    GUI::PaintFocusedWidget();
    gfx_BlitBuffer();
    
    if (key == sk_Up)
      GUI::MoveFocusBack();
    
    if (key == sk_Down)
      GUI::MoveFocusForward();
    
    if (key == sk_Clear)
      exit = true;
    
    if ((key == sk_2nd) || (key == sk_Enter))
      name_selected = true;
    
  } while (!exit && !name_selected);
  
  GUI::RemoveAllUnfocusableWidgets();
  GUI::RemoveAllFocusableWidgets();
  
  if (name_selected)
    strncpy(pack_name, pack_list.GetCurrPackName(), PACK_NAME_LEN);
  
  if (exit)
    *exit_menu = true;
  
  return pack_name;
}


void mainfuncs_EditPack(const char *name)
{
  const uint8_t NUM_INVINCIBLE_STATES = 2;
  const char *INVINCIBLE_STATES[NUM_INVINCIBLE_STATES] = {
    "No", "Yes"
  };
  const uint8_t NUM_OIRAM_SUITS   = 4;
  const uint8_t OIRAM_SUIT_SMALL  = 0;
  const uint8_t OIRAM_SUIT_BIG    = 1;
  const uint8_t OIRAM_SUIT_FIRE   = 2;
  const uint8_t OIRAM_SUIT_RACOON = 3;
  const char *OIRAM_SUITS[NUM_OIRAM_SUITS] = {
    "Small", "Big", "Fire", "Racoon"
  };
  
  bool all_values_valid = false;
  bool exit = false;
  bool exit_save = false;
  sk_key_t key;
    
  EditorBackground ebg;
  GUI::AddUnfocusableWidget(&ebg);
  
  LevelPack lp(name);
  
  OiramAnimation oiram_anim(
    0, 0, 320, 110, lp.GetFlags(), lp.GetOiramFlagInvincible()
  );
  GUI::AddUnfocusableWidget(&oiram_anim);
  
  NumericalInput ni_progress(50, 120);
  ni_progress.ForceSetNumberTo(lp.GetProgress() + 1);
  ni_progress.SetMinValue(1);

  ni_progress.SetMaxValue(lp.GetNumLevels());
  GUI::AddFocusableWidget(&ni_progress);
  
  NumericalInput ni_coins(50, 140);
  ni_coins.ForceSetNumberTo(lp.GetCoins());
  ni_coins.SetMaxValue(255);
  GUI::AddFocusableWidget(&ni_coins);
  
  NumericalInput ni_lives(50, 160);
  ni_lives.ForceSetNumberTo(lp.GetLives());
  ni_lives.SetMinValue(1);
  ni_lives.SetMaxValue(MAX_NUM_LIVES);
  GUI::AddFocusableWidget(&ni_lives);
  
  HorizListMenu hlm_invincible(INVINCIBLE_STATES, NUM_INVINCIBLE_STATES, 0, 100, 180);
  GUI::AddFocusableWidget(&hlm_invincible);
  
  HorizListMenu hlm_suits(OIRAM_SUITS, NUM_OIRAM_SUITS, lp.GetFlags(), 50, 200);
  GUI::AddFocusableWidget(&hlm_suits);
  
  // The length of the buffer should be 9 = strlen("16777215") + NULL
  NumericalInput ni_score(9, 50, 220, 150, NUMERICAL_INPUT_STD_FIELD_HEIGHT);
  ni_score.ForceSetNumberTo(lp.GetScore());
  ni_score.SetMaxValue(16777215);
  GUI::AddFocusableWidget(&ni_score);
  
  GUI::PaintAllUnfocusableWidgets();
  GUI::PaintAllFocusableWidgets();
  
  do
  {
    delay(100);
    
    kb_Scan();
    key = asm_GetCSC();
    
    if (!hlm_invincible.GetOffset())
      lp.ResetOiramFlagInvincible();
    else
      lp.SetOiramFlagInvincible();
      
    oiram_anim.SetOiramInvincibility(lp.GetOiramFlagInvincible());
    
    if (hlm_suits.GetOffset() == OIRAM_SUIT_SMALL)
      lp.SetOiramFlagSmall();
    
    if (hlm_suits.GetOffset() == OIRAM_SUIT_BIG)
      lp.SetOiramFlagBig();
      
    if (hlm_suits.GetOffset() == OIRAM_SUIT_FIRE)
      lp.SetOiramFlagFire();
      
    if (hlm_suits.GetOffset() == OIRAM_SUIT_RACOON)
      lp.SetOiramFlagRacoon();
    
    // Set the suit on each iteration in case the user changed the suit.
    oiram_anim.SetOiramSuit(lp.GetFlags());
    
    GUI::RunFocusedWidget();
    GUI::PaintFocusedWidget();
    GUI::RunUnfocusableWidget(1);
    GUI::PaintUnfocusableWidget(1);
    gfx_BlitBuffer();
    
    if (key == sk_Up)
      GUI::MoveFocusBack();
    
    if (key == sk_Down)
      GUI::MoveFocusForward();
    
    if (key == sk_Clear)
      exit = true;
    
    if ((key == sk_2nd) || (key == sk_Enter))
    {
      // Allow the user to exit if and only if all entered values are valid.
      all_values_valid = ni_progress.IsValidValue();
      all_values_valid = (ni_coins.IsValidValue() & all_values_valid);
      all_values_valid = (ni_lives.IsValidValue() & all_values_valid);
      all_values_valid = (ni_score.IsValidValue() & all_values_valid);
      
      if (all_values_valid)
        exit_save = true;
    }
    
  } while (!exit && !exit_save);
  
  if (exit_save)
  {
    lp.SetProgress(ni_progress.GetValue() - 1);
    lp.SetCoins(ni_coins.GetValue());
    lp.SetLives(ni_lives.GetValue());
    lp.SetScore(ni_score.GetValue());
    lp.WriteConfig();

  }
  
  GUI::RemoveAllUnfocusableWidgets();
  GUI::RemoveAllFocusableWidgets();
  return;
}


void mainfuncs_OiramSaveAppvarError()
{
  gfx_FillScreen(color_WHITE);
  gfx_SetTextBGColor(color_WHITE);
  gfx_SetTextFGColor(color_BLACK);
  gfx_SetTextTransparentColor(color_WHITE);
  gfx_PrintStringXY("Oiram save appvar does not exist.", 1, 1);
  gfx_PrintStringXY("Run Oiram before executing this program.", 1, 16);
  gfx_PrintStringXY("Press any key...", 1, 31);
  gfx_BlitBuffer();
  while (!os_GetCSC());
  return;
}