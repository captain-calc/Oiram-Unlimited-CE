// Name:    Captain Calc
// Date:    August 5, 2021
// File:    ccdbg.h
// Purpose: ccdbg provides macros for pretty-printing variable values.


#ifndef CCDBG_H
#define CCDBG_H


//#include <debug.h>   // For dbg_sprintf(), dbgout

#include <string.h>  // For strlen()

#include <stdio.h>
#define dbgout ((char*)0xFB0000)
#define dbgerr ((char*)0xFC0000)
#define dbg_sprintf sprintf


#define VALUE_INDENT 50

static unsigned int CCDBG_CHKPT_INDENT = 0;


#define CCDBG_CHKPT_START     \
  do {                        \
    CCDBG_CHKPT_INDENT += 4; \
  } while (0)


#define CCDBG_CHKPT_END       \
  do {                        \
    CCDBG_CHKPT_INDENT -= 4; \
  } while (0)


#define CCDBG_PRINT_CHKPT_INDENT                          \
  do {                                                    \
    for (unsigned int i = 0; i < CCDBG_CHKPT_INDENT; i++) \
    {                                                     \
      dbg_sprintf(dbgout, " ");                           \
    }                                                     \
    dbg_sprintf(dbgout, "|");                             \
  } while(0)


#define CCDBG_PRINT_FUNCTION_HEADER(name)        \
  do {                                           \
    dbg_sprintf(dbgout, "\n");                   \
    CCDBG_PRINT_CHKPT_INDENT;                    \
    dbg_sprintf(dbgout, "%s()\n", name);         \
    CCDBG_PRINT_CHKPT_INDENT;                    \
    for (int i = VALUE_INDENT + 15; i > 0; i--)  \
    {                                            \
      dbg_sprintf(dbgout, "-");                  \
    }                                            \
    dbg_sprintf(dbgout, "\n");                   \
  } while (0)


#define CCDBG_PRINT_SECTION_HEADER(name)   \
  do {                                     \
    CCDBG_PRINT_CHKPT_INDENT;              \
    dbg_sprintf(dbgout, "  %s\n", name);   \
  } while (0)


#define CCDBG_PRINT_MSG(msg)              \
  do {                                    \
    CCDBG_PRINT_CHKPT_INDENT;             \
    dbg_sprintf(dbgout, "    %s\n", msg); \
  } while (0)


#define CCDBG_DUMP_PTR(varname)                               \
  do {                                                        \
    CCDBG_PRINT_CHKPT_INDENT;                                 \
    dbg_sprintf(dbgout, "    %s", #varname);                  \
    for (int i = VALUE_INDENT - strlen(#varname); i > 0; i--) \
    {                                                         \
      dbg_sprintf(dbgout, " ");                               \
    }                                                         \
    dbg_sprintf(dbgout,"= 0x%6x\n", (unsigned int)varname);   \
  } while (0)


#define CCDBG_DUMP_INT(varname)                               \
  do {                                                        \
    CCDBG_PRINT_CHKPT_INDENT;                                 \
    dbg_sprintf(dbgout, "    %s", #varname);                  \
    for (int i = VALUE_INDENT - strlen(#varname); i > 0; i--) \
    {                                                         \
      dbg_sprintf(dbgout, " ");                               \
    }                                                         \
    dbg_sprintf(dbgout,"= %d\n", varname);                    \
  } while (0)


#define CCDBG_DUMP_STR(varname)                               \
  do {                                                        \
    CCDBG_PRINT_CHKPT_INDENT;                                 \
    dbg_sprintf(dbgout, "    %s", #varname);                  \
    for (int i = VALUE_INDENT - strlen(#varname); i > 0; i--) \
    {                                                         \
      dbg_sprintf(dbgout, " ");                               \
    }                                                         \
    dbg_sprintf(dbgout,"= %s\n", varname);                    \
  } while (0)

#endif