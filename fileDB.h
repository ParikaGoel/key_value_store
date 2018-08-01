#ifndef CSV_H
#define CSV_H

#include "fstream"
#include "string"
#include "vector"
#include "fstream"

using namespace std;

class fileDB {
private:
	std::fstream m_file;
public:
	fileDB();
	~fileDB();
	int open(std::string &filename);
	string read(string key);
	void write(string key, string value);
	void modify(string key, string value);
	void remove(string key);
};

#endif