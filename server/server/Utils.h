/*
 * Something functions
*/

#ifndef UTILS_H
#define UTILS_H

// printing error
void throw_error(const char* error_text);

// checking existions of directory
bool dirExists(const std::string& dirName_in);

// parsing a command
int parse(std::string comm);

#endif // UTILS_H
