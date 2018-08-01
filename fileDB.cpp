#include "fileDB.h"
#include "iostream"

fileDB::fileDB() {

}

fileDB::~fileDB() {
	if (m_file.is_open())
		m_file.close();
}

int fileDB::open(std::string &filename) {
	m_file.open(filename.c_str(), std::ios::in | std::ios::out);
	if (!m_file) {
		std::cerr << "Failed to open file\n";
		return EXIT_FAILURE;
	}
	return 0;
}

string fileDB::read(string key) {
	std::string row;

	while (std::getline(m_file, row) && row[0] != '#') {
		std::size_t pos = row.find(',');
		std::string retrieved_key = row.substr(0, pos);
		std::string retrieved_value = row.substr(pos+1);
		if (retrieved_key == key)
			return retrieved_value;
	}

	return "\0";
}

void fileDB::write(string key, string value) {
	m_file.seekp(0, ios_base::end);
	string fileEntry = key + "," + value + "\n";
	m_file << fileEntry;
}

void fileDB::modify(string key, string value){
	std::string row;
	m_file.seekg(0, ios_base::beg);
	while (std::getline(m_file, row)) {
		if (row[0] != '#') {
			std::size_t pos = row.find(',');
			std::string retrieved_key = row.substr(0, pos);
			std::string retrieved_value = row.substr(pos + 1);
			if (retrieved_key == key) {
				std::size_t currentPos = m_file.tellg();
				std::size_t length = row.length() + 2;
				m_file.seekp(currentPos - length);
				m_file << '#';
				break;
			}
		}
	}
	write(key, value);
}

void fileDB::remove(string key) {
	std::string row;
	while (std::getline(m_file, row) && row[0] != '#') {
		std::size_t pos = row.find(',');
		std::string retrieved_key = row.substr(0, pos);
		std::string retrieved_value = row.substr(pos + 1);
		if (retrieved_key == key) {
			std::size_t currentPos = m_file.tellg();
			std::size_t length = row.length();
			m_file.seekp(currentPos - length);
			m_file << "#";
		}
	}
}