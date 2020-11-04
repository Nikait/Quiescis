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
		<< "            ##                                                                            \n";
#ifndef __linux__
	SetConsoleTextAttribute(hConsole, 10);
	std::cout << "            #";
	SetConsoleTextAttribute(hConsole, 13);
	std::cout << "                                         Quiescis RAT ";
	SetConsoleTextAttribute(hConsole, 7);
	std::cout << "1.3.1 ";
	SetConsoleTextAttribute(hConsole, 13);
	std::cout << "by Nikait               \n";
	SetConsoleTextAttribute(hConsole, 10);
	std::cout << "           *";
	
	
	std::cout << "                                          github:";
	SetConsoleTextAttribute(hConsole, 13);
	std::cout << "  https://github.com/Nikait   \n";
	SetConsoleTextAttribute(hConsole, 10);
	std::cout << "          *";
	std::cout << "                                           twitter:";
	SetConsoleTextAttribute(hConsole, 13);
	std::cout << " @aaanikit\n\n";
	SetConsoleTextAttribute(hConsole, 7);
#else
	std::cout << green << "            #" << purpure;
	std::cout << "                                         Quiescis RAT " << st_end;
	std::cout << "1.3.1" << purpure << " by Nikait               \n";
	std::cout << green << "           *" << "                                          github:";
	std::cout << purpure << "  https://github.com/Nikait   \n" << green;
	std::cout << "          *                                           twitter:";
	std::cout << purpure << " @aaanikit\n" << st_end << std::endl;
	
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
		<< "--------------------------------------------------------\n"
		<< "|1 | [help]         - print help menu                  |\n"
		<< "|2 | [close]        - close connection                 |\n"
		<< "|3 | [pwd]          - path                             |\n"
		<< "|4 | [ls]           - list files and dirs              |\n"
		<< "|5 | [rm]           - delete file                      |\n"
		<< "|6 | [rmdir]        - delete directory                 |\n"
		<< "|7 | [info]         - information (os, cpu, gpu, etc)  |\n"
		<< "--------------------------------------------------------\n";
#ifndef __linux__
	SetConsoleTextAttribute(hConsole, 10);
	std::cout << "\nadvanced:\n";
	SetConsoleTextAttribute(hConsole, 7);
#else
	std::cout << green << "\nadvanced:\n" << st_end;
#endif

	std::cout
		<< "--------------------------------------------------------\n"
		<< "|8 | [ps]           - process info                     |\n"
		<< "|9 | [kill]         - kill process                     |\n"
		<< "|10| [keylogger]    - start keylogger                  |\n"
		<< "|11| [cryptfile]    - encrypt file      with using XOR |\n"
		<< "|12| [cryptdir]     - encrypt directory with using XOR |\n"
		<< "|13| [download]     - download file                    |\n"
#if chrome_stealer
		<< "|16| [chrome_st]    - chrome stealer                   |\n"
#endif // chrome_stealer
		<< "-------------------------------------------------------\n";
#ifndef __linux__
	SetConsoleTextAttribute(hConsole, 10);
	std::cout << "\ntrolling:\n";
	SetConsoleTextAttribute(hConsole, 7);
#else
	std::cout << green << "\ntrolling:\n" << st_end;
#endif

	std::cout
		<< "--------------------------------------------------------\n"
		<< "|14| [shutdown]     - shuting down                     |\n"
		<< "|15| [error]        - print error (english only)       |\n"
		<< "--------------------------------------------------------\n" << std::endl;
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
	std::cout << "[" << green << time_buf << st_end << "]";
#endif
}

