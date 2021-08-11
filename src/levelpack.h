// Name:    Captain Calc
// Date:    August 10, 2021
// File:    levelpack.h
// Purpose: This file declares the LevelPack class. This class holds all of the
//          data pertaining to an Oiram level pack.


#ifndef LEVELPACK_H
#define LEVELPACK_H


#include <fileioc.h>

#include "defines.h"  // For PACK_NAME_LEN


#define FLAG_OIRAM_RESET        0
#define FLAG_OIRAM_BIG          1
#define FLAG_OIRAM_FIRE         2
#define FLAG_OIRAM_INVINCIBLE   4
#define FLAG_OIRAM_SLIDE        8   // Not used
#define FLAG_OIRAM_RACOON      16

#define MAX_NUM_LIVES  99


// This is the structure of an Oiram level pack save configuration in the Oiram
// save appvar.
typedef struct
{
  uint8_t  progress;
  uint8_t  coins;
  uint8_t  lives;
  uint8_t  flags;
  uint24_t score;
  char     name[PACK_NAME_LEN];
} pack_config_t;


// Description: LevelPack() (parameterized constructor) creates a new LevelPack
//              instance loaded with the specified level pack's configuration
//              and number of levels.
// Note:        The constructor assumes that ReadConfig() will execute
//              successfully. If it does not, m_NumLevels will be set to one.
// Pre:         <name> must specify a level pack in the calculator's RAM or
//              Archive.
// Post:        New LevelPack instance created.


// Description: ReadConfig() loads the class's private <m_PackConfig> with the
//              specified pack's configuration.
// Pre:         <name> must specify a level pack in the calculator's RAM or
//              Archive.
// Post:        <m_PackConfig> loaded with level pack's configuration and true
//              returned. False returned if file operations failed.


// Description: ReadNumLevels() gets the number of levels for the represented
//              level pack.
// Pre:         ReadConfig() must be executed successfully before this function
//              is called.
// Post:        <m_NumLevels> loaded with the represented level pack's number
//              of levels.


// Description: WriteConfig() overwrites the represented level pack's
//              configuration in the Oiram save appvar with the configuration
//              given by <m_PackConfig>.
// Pre:         Represented level pack must exist in Oiram save appvar.
// Post:        Represented level pack configuration written to Oiram save
//              appvar and true returned. False returned if file operations
//              failed.


// Description: SetProgress() sets the <progress> of the <m_PackConfig>.
// Pre:         <progress> must be less than or equal to the number of levels
//              in the level pack.
// Post:        <progress> written to <m_PackConfig->progress>.


// Description: SetCoins() sets the <coins> of the <m_PackConfig>.
// Pre:         None
// Post:        <coins> written to <m_PackConfig->coins>.


// Description: SetLives() sets the <lives> of the <m_PackConfig>.
// Pre:         <lives> must be less than or equal to the MAX_NUM_LIVES.
// Post:        <lives> written to <m_PackConfig->lives>.


// Description: SetScore() sets the <score> of the <m_PackConfig>.
// Pre:         None
// Post:        <score> written to <m_PackConfig->score>.


// Description: SetOiramFlagSmall() resets all Oiram flags, except
//              FLAG_OIRAM_INVINCIBLE.
// Pre:         None
// Post:        <m_PackConfig->flags> equals FLAG_OIRAM_INVINCIBLE.


// Description: SetOiramFlagBig() sets FLAG_OIRAM_BIG.
// Pre:         None
// Post:        FLAG_OIRAM_BIG and FLAG_OIRAM_INVINCIBLE set in
//              <m_PackConfig->flags>.


// Description: SetOiramFlagFire() sets FLAG_OIRAM_BIG and FLAG_OIRAM_FIRE.
// Pre:         None
// Post:        FLAG_OIRAM_BIG and FLAG_OIRAM_FIRE set in
//              <m_PackConfig->flags>.


// Description: SetOiramFlagInvincible() sets FLAG_OIRAM_INVINCIBLE.
// Pre:         None
// Post:        FLAG_OIRAM_INVINCIBLE set in <m_PackConfig->flags>.


// Description: ResetOiramFlagInvincible() resets FLAG_OIRAM_INVINCIBLE.
// Pre:         None
// Post:        FLAG_OIRAM_INVINCIBLE reset in <m_PackConfig->flags>.


// Description: SetOiramFlagRacoon() sets FLAG_OIRAM_BIG and FLAG_OIRAM_RACOON.
// Pre:         None
// Post:        FLAG_OIRAM_BIG and FLAG_OIRAM_RACOON set in
//              <m_PackConfig->flags>.


// Description: GetProgress() returns the number of levels completed in the
//              pack.
// Pre:         None
// Post:        <m_PackConfig->progress> returned.


// Description: GetCoins() returns the number of coins obtained in the pack.
// Pre:         None
// Post:        <m_PackConfig->coins> returned.


// Description: GetLives() returns the number of lives in the pack.
// Pre:         None
// Post:        <m_PackConfig->lives> returned.


// Description: GetFlags() returns the flag byte of the pack configuration.
// Pre:         None
// Post:        <m_PackConfig->flags> returned.


// Description: GetScore() returns the current score in the pack.
// Pre:         None
// Post:        <m_PackConfig->score> returned.


// Description: GetNumLevels() returns the total number of levels in the pack.
// Pre:         None
// Post:        <m_NumLevels> returned.


// Description: GetOiramFlagSmall() checks if none of the Oiram flags are set,
//              excluding FLAG_OIRAM_INVINCIBLE.
// Pre:         None
// Post:        True returned if none of the flags are set, excluding
//              FLAG_OIRAM_INVINCIBLE. False returned otherwise.


// Description: GetOiramFlagBig() checks if FLAG_OIRAM_BIG is set.
// Pre:         None
// Post:        State of FLAG_OIRAM_BIG returned.


// Description: GetOiramFlagFire() checks if FLAG_OIRAM_FIRE is set.
// Pre:         None
// Post:        State of FLAG_OIRAM_FIRE returned.


// Description: GetOiramFlagInvincible() checks if FLAG_OIRAM_INVINCIBLE is
//              set.
// Pre:         None
// Post:        State of FLAG_OIRAM_INVINCIBLE returned.


// Description: GetOiramFlagRacoon() checks if FLAG_OIRAM_RACOON is set.
// Pre:         None
// Post:        State of FLAG_OIRAM_RACOON returned.


// Description: ~LevelPack() destroys a LevelPack instance.
// Pre:         <m_PackConfig> must point to memory allocated with "new".
// Post:        LevelPack instance destroyed.


class LevelPack
{
  private:
    pack_config_t *m_PackConfig;
    uint8_t        m_NumLevels;
    
  public:
    LevelPack(const char name[]);
    
    bool ReadConfig(const char name[]);
    bool ReadNumLevels();
    bool WriteConfig();
    
    void SetProgress(const uint8_t progress)
      { m_PackConfig->progress = progress; }
    void SetCoins(const uint8_t coins) { m_PackConfig->coins = coins; }
    void SetLives(const uint8_t lives) { m_PackConfig->lives = lives; }
    void SetScore(const uint24_t score) { m_PackConfig->score = score; }
    
    void SetOiramFlagSmall();
    void SetOiramFlagBig();
    void SetOiramFlagFire();
    void SetOiramFlagInvincible();
    void ResetOiramFlagInvincible();
    void SetOiramFlagRacoon();
    
    uint8_t GetProgress() const { return m_PackConfig->progress; }
    uint8_t GetCoins() const { return m_PackConfig->coins; }
    uint8_t GetLives() const { return m_PackConfig->lives; }
    uint8_t GetFlags() const { return m_PackConfig->flags; }
    uint24_t GetScore() const { return m_PackConfig->score; }
    uint8_t GetNumLevels() const { return m_NumLevels; }
    
    bool GetOiramFlagSmall() const;
    bool GetOiramFlagBig() const;
    bool GetOiramFlagFire() const;
    bool GetOiramFlagInvincible() const;
    bool GetOiramFlagRacoon() const;
    
    ~LevelPack() { delete m_PackConfig; }
};

#endif