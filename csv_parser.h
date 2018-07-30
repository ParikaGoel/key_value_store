#ifndef CSV_H
#define CSV_H

#include "fstream"
#include "string"
#include "vector"
#include "key_value_store.h"

class csv_parser {
private:
	std::fstream m_file;
public:
	csv_parser();
	~csv_parser();
	int open(std::string &filename);
	string read(string key);
	void write(string key, string value);
	void remove(string key);
};

#endif