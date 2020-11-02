#include <string>

#include "Config.h"

#ifndef CHROME_H
#define CHROME_H

#if chrome_stealer
std::string GetChromeHistory();
std::string GetChromeDownloads();
std::string GetChromeRequests();
#endif

#endif