#ifndef DB_H
#define DB_H

#include <iostream>
#include <map>
#include <string>
#include <queue>
#include "fileDB.h"

using namespace std;

// Class "Value"
// Member Variables :
//	m_str : String variable storing the value string
//	m_available : Boolean variable denoting whether the
//		value is available for write operation or not
class Value {
	string m_str;
	bool m_available;
public:
	Value() {
		m_available = true;
		m_str = " ";
	}
	bool isAvailable();
	string getValue();
	void setValue(string new_str);
	void setAvailability(bool avail);
};

// Class evictionFIFO : Implementation of eviction strategy (FIFO)
class evictionFIFO {
	queue <string> evictionQueue;
public:
	size_t getSize();
	string getFrontElement();
	void updateEvictionQueue(string new_key);
	void pushEntry(string key);
	void evict();
};

// Class mapDB : Implementation of key value store
// Member variables :
//	store : a map variables which map a key string to an object of value class
class MapDB {
	map<string, Value> cache;
	fileDB m_file;
	evictionFIFO evictionTable;
	size_t evictionTableSize;
public:
	MapDB(size_t size = 10) {
		evictionTableSize = size;
		string filename("fileDB.csv");
		m_file.open(filename);
	}
	string get(string key);
	void set(string key, string value);
	void remove(string key);
};

#endif