#pragma once

#include <iostream>

// SIMPLE LOGGER. LOG_LEVEL: (0) off, (1) info, (2) debug
#define LOG_LEVEL 0

#define LOG_INFO(msg) if(LOG_LEVEL  > 0) std::wcerr << " (INFO): " << msg << std::endl;
#define LOG_DEBUG(msg) if(LOG_LEVEL > 1) std::wcerr <<" (DEBUG): " << msg " ::" << __FILE__ << ":" << __LINE__ << std::endl;
