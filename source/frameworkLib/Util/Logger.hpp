#pragma once

#include <iostream>

// Global simple logger
// LOG_LEVEL:
// (0) off
// (3) info
// (2) debug
// (1) critical
#define LOG_LEVEL 1

#define LOG_CRITICAL(msg) if(LOG_LEVEL >= 1) std::wcerr << " (DEBUG): " << msg << std::endl;
#define LOG_DEBUG(msg) if(LOG_LEVEL >= 2) std::wcerr << " (DEBUG): " << msg << std::endl;
#define LOG_DEBUG_EXT(msg) if(LOG_LEVEL >= 2) std::wcerr << " (DEBUG): " << msg " ::" << __FILE__ << ":" << __LINE__ << std::endl;
#define LOG_INFO(msg) if(LOG_LEVEL  >= 3) std::wcerr << " (INFO): " << msg << std::endl;
