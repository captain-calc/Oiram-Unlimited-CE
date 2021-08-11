// Name:    Captain Calc
// Date:    August 10, 2021
// File:    levelpack.cpp
// Purpose: This file provides the definitions of the LevelPack class member
//          functions declared in levelpack.h.


#include <stdint.h>
#include <string.h>  // For memcmp

#include <fileioc.h>

#include "ccdbg.h"
#include "cutil.h"
#include "defines.h"
#include "levelpack.h"


LevelPack::LevelPack(const char name[])
{
  m_PackConfig = new pack_config_t;
  
  if (ReadConfig(name))
    ReadNumLevels();
  else
    m_NumLevels = 1;
}


bool LevelPack::ReadConfig(const char name[])
{
  ti_var_t slot;
  uint8_t num_packs;
  uint8_t pack = 0;
  bool pack_found = false;
  
  if ((slot = ti_Open(OIRAM_SAVE_APPVAR, "r")))
  {
    ti_Read(&num_packs, 1, 1, slot);
    
    while ((pack < num_packs) && !pack_found)
    {
      ti_Read(m_PackConfig, sizeof(pack_config_t), 1, slot);
      
      // Both strings should be NULL-terminated.
      if (!strcmp(m_PackConfig->name, name))
        pack_found = true;
      
      pack++;
    }
    
    ti_Close(slot);
  }
  
  return pack_found;
}


bool LevelPack::ReadNumLevels()
{
  ti_var_t slot;
  uint8_t *pack_ptr;
  bool read_num_levels = false;
  
  if ((slot = ti_Open(m_PackConfig->name, "r")))
  {
    pack_ptr = cutil_GetPackPointer(slot);
    pack_ptr += strlen((char *)pack_ptr) + 1;
    pack_ptr += strlen((char *)pack_ptr) + 1;
    m_NumLevels = *pack_ptr;
    read_num_levels = true;
    ti_Close(slot);
  }
  
  return read_num_levels;
}


bool LevelPack::WriteConfig()
{
  pack_config_t *temp = new pack_config_t;
  ti_var_t slot;
  uint8_t num_packs;
  uint8_t pack = 0;
  bool config_written = false;
  
  ti_CloseAll();
  
  if ((slot = ti_Open(OIRAM_SAVE_APPVAR, "r+")) && (temp != nullptr))
  {
    ti_Read(&num_packs, 1, 1, slot);
    
    while ((pack < num_packs) && !config_written)
    {
      ti_Read(temp, sizeof(pack_config_t), 1, slot);
      
      if (!strcmp(m_PackConfig->name, temp->name))
      {
        ti_Seek(-sizeof(pack_config_t), SEEK_CUR, slot);
        ti_Write(m_PackConfig, sizeof(pack_config_t), 1, slot);
        config_written = true;
      }
      
      pack++;
    }
    
    ti_Close(slot);
    delete temp;
  }
  
  return config_written;
}


void LevelPack::SetOiramFlagSmall()
{
  // Preserve the INVINCIBLE flag, reset all others.
  m_PackConfig->flags &= FLAG_OIRAM_INVINCIBLE;
  return;
}


void LevelPack::SetOiramFlagBig()
{
  m_PackConfig->flags &= FLAG_OIRAM_INVINCIBLE;
  m_PackConfig->flags |= FLAG_OIRAM_BIG;
  return;
}


void LevelPack::SetOiramFlagFire()
{
  m_PackConfig->flags &= FLAG_OIRAM_INVINCIBLE;
  m_PackConfig->flags |= FLAG_OIRAM_BIG | FLAG_OIRAM_FIRE;
  return;
}


void LevelPack::SetOiramFlagInvincible()
{
  m_PackConfig->flags |= FLAG_OIRAM_INVINCIBLE;
  return;
}


void LevelPack::ResetOiramFlagInvincible()
{
  if (m_PackConfig->flags & FLAG_OIRAM_INVINCIBLE)
    m_PackConfig->flags ^= FLAG_OIRAM_INVINCIBLE;
  return;
}


void LevelPack::SetOiramFlagRacoon()
{
  m_PackConfig->flags &= FLAG_OIRAM_INVINCIBLE;
  m_PackConfig->flags |= FLAG_OIRAM_BIG | FLAG_OIRAM_RACOON;
  return;
}


bool LevelPack::GetOiramFlagSmall() const
{
  return ~(m_PackConfig->flags ^ FLAG_OIRAM_INVINCIBLE);
}


bool LevelPack::GetOiramFlagBig() const
{
  return (m_PackConfig->flags & FLAG_OIRAM_BIG);
}


bool LevelPack::GetOiramFlagFire() const
{
  return (m_PackConfig->flags & FLAG_OIRAM_FIRE);
}


bool LevelPack::GetOiramFlagInvincible() const
{
  return (m_PackConfig->flags & FLAG_OIRAM_INVINCIBLE);
}


bool LevelPack::GetOiramFlagRacoon() const
{
  return (m_PackConfig->flags & FLAG_OIRAM_RACOON);
}