#include "csv_parser.h"

csv_parser::csv_parser() {

}

csv_parser::~csv_parser() {
	if (m_file.is_open())
		m_file.close();
}

int csv_parser::open(std::string &filename) {
	m_file.open(filename.c_str(), std::ios::in | std::ios::out);
	if (!m_file.is_open())
		return -1;
	return 0;
}

string csv_parser::read(string key) {
	std::string row;

	while (std::getline(m_file, row)) {
		std::size_t pos = row.find(',');
		std::string retrieved_key = row.substr(0, pos);
		std::string retrieved_value = row.substr(pos+1);
		if (retrieved_key == key)
			return retrieved_value;
	}

	return NULL;
}

void csv_parser::write(string key, string value) {
	m_file.seekp(0, ios_base::end);
	string fileEntry = key + "," + value;
	m_file << fileEntry;
}

void csv_parser::remove(string key) {

}