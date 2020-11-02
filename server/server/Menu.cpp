#include <iostream>
#include <ctime>
#include "Menu.h"
#include "Config.h"

#ifndef  __linux__
	#include <windows.h>
	#pragma warning(disable: 4996)
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

void PrintGreeting() {
#ifndef __linux__
	SetConsoleTextAttribute(hConsole, 10);
#else
	std::cout << green;
#endif
	std::cout <<
		   "      # ###                                                                               \n"
		<< "    #  ####                    #                                       #                  \n"
		<< "   #  #  ###                  ###                                     ###                 \n"
		<< "  #  ##   ###                  #                                       #                  \n"
		<< " #  ###    ### ##    ###                          #####                          ####     \n"
		<< "##   ##     ##  ##    ###    ###        ##      # #### #    ####      ###     # #### #    \n"
		<< "##   ##     ##  ##     ####   ###      # ###    ##  ####    # ###      ##     ##  ####    \n"
		<< "##   ##     ##  ##      ##     ##     #   ###  ####        #   ####    ##    ####         \n"
		<< "##   ##     ##  ##      ##     ##    ##    ###   ###      ##           ##      ###        \n"
		<< "##   ##     ##  ##      ##     ##    ########      ###    ##           ##        ###      \n"
		<< " ##  ## ### ##  ##      ##     ##    #######         ###  ##           ##          ###    \n"
		<< "  ## #   ####   ##      ##     ##    ##         ####  ##  ##           ##     ####  ##    \n"
		<< "   ###     ###   ####### ##    ##    ####    # # #### #   ###     #    ##    # #### #     \n"
		<< "    ####### ##    #####   ##   ### #  #######     ####     #######     ### #    ####      \n"
		<< "      ###   ##                  ###    #####                #####       ###               \n"
		<< "            ##  ";
#ifndef __linux__
	SetConsoleTextAttribute(hConsole, 13);
	std::cout << "                                   -------------------------------------- \n";
	SetConsoleTextAttribute(hConsole, 10);
	std::cout << "            #";
	SetConsoleTextAttribute(hConsole, 13);
	std::cout << "                                      |  Quiescis Rat                      | \n";
	SetConsoleTextAttribute(hConsole, 10);
	std::cout << "           *";
	SetConsoleTextAttribute(hConsole, 13);
	std::cout << "                                       |  development by Nikait             | \n";
	SetConsoleTextAttribute(hConsole, 10);
	std::cout << "          *";
	SetConsoleTextAttribute(hConsole, 13);
	std::cout << "                                        |  github: https://github.com/Nikait | \n"
		<< "                                                   -------------------------------------- \n" << std::endl;
	SetConsoleTextAttribute(hConsole, 7);
#else
	std::cout << purpure
		<< "                                   -------------------------------------- \n"
		<< green
		<< "            #" << purpure << "                                      |  Quiescis Rat                      | \n"
		<< green
		<< "           *" << purpure << "                                       |  development by Nikait             | \n"
		<< green
		<< "          *" << purpure << "                                        |  github: https://github.com/Nikait | \n"
		<< "                                                   -------------------------------------- \n" << st_end << std::endl;
	
#endif
}

void HelpMenu() {
#ifndef __linux__
	std::cout << "\t\t     HELP [";
	SetConsoleTextAttribute(hConsole, 12);
	std::cout << "MENU";
	SetConsoleTextAttribute(hConsole, 7);
	std::cout << "]\n";
	SetConsoleTextAttribute(hConsole, 10);
	std::cout << "\nbase:\n";
	SetConsoleTextAttribute(hConsole, 7);
#else
	std::cout << "\t\t     HELP [" << red << "MENU" << st_end << "]\n";
	std::cout << green << "\nbase:\n" << st_end;
#endif
	std::cout
		<< "-----------------------------------------------------\n"
		<< "| [close]        - close connection                 |\n"
		<< "| [pwd]          - path                             |\n"
		<< "| [ls]           - list files and dirs              |\n"
		<< "| [rm] [rmdir]   - delete file; delete directory    |\n"
		<< "| [info]         - information (os, cpu, gpu, ram)  |\n"
		<< "-----------------------------------------------------\n";
#ifndef __linux__
	SetConsoleTextAttribute(hConsole, 10);
	std::cout << "\nadvanced:\n";
	SetConsoleTextAttribute(hConsole, 7);
#else
	std::cout << green << "\nadvanced:\n" << st_end;
#endif

	std::cout
		<< "-----------------------------------------------------\n"
		<< "| [ps]           - process info                     |\n"
		<< "| [kill]         - kill process                     |\n"
		<< "| [keylogger]    - start keylogger                  |\n"
		<< "| [cryptfile]    - encrypt file      with using XOR |\n"
		<< "| [cryptdir]     - encrypt directory with using XOR |\n"
		<< "| [download]     - download file                    |\n"
#if chrome_stealer
		<< "| [chrome_st]    - chrome stealer                   |\n"
#endif // chrome_stealer
		<< "-----------------------------------------------------\n";
#ifndef __linux__
	SetConsoleTextAttribute(hConsole, 10);
	std::cout << "\ntrolling:\n";
	SetConsoleTextAttribute(hConsole, 7);
#else
	std::cout << green << "\ntrolling:\n" << st_end;
#endif

	std::cout
		<< "-----------------------------------------------------\n"
		<< "| [shutdown]     - shuting down                     |\n"
		<< "| [error]        - print error (english only)       |\n"
		<< "-----------------------------------------------------\n" << std::endl;
}

// print timer in format: [hh:mm:ss]
void timenow() {
	char time_buf[80];
	time_t seconds = time(NULL);
	tm* timeinfo = localtime(&seconds);
	const char* format = "%H:%M:%S";
	strftime(time_buf, 80, format, timeinfo);
#ifndef __linux__
	std::cout << "[";
	SetConsoleTextAttribute(hConsole, 10);
	std::cout << time_buf;
	SetConsoleTextAttribute(hConsole, 7);
	std::cout << "]";
#else
	std::cout << "[";
	std::cout << time_buf;
	std::cout << "]";
#endif
}

