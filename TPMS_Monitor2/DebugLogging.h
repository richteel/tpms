#ifndef DEBUGLOGGING_H
#define DEBUGLOGGING_H

#include <map>

/*****************************************************************************
 *                                   ENUMS                                   *
 *****************************************************************************/

enum class DebugLevels {
  Verbose = 0,
  Info = 1,
  Warning = 2,
  Error = 3
};

/*****************************************************************************
 *                                  MAPPINGS                                 *
 *****************************************************************************/
 static std::map<DebugLevels, const char*> debugLevelName{
  { DebugLevels::Verbose, "Verbose" },
  { DebugLevels::Info, "Info" },
  { DebugLevels::Warning, "Warning" },
  { DebugLevels::Error, "Error" }
};


#endif    // DEBUGLOGGING_H