#include <iostream>
#include <map>
#include <string>

using namespace std;

// Class "value"
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

// Class mapDB : Implementation of key value store
// Member variables :
//	store : a map variables which map a key string to an object of value class
class MapDB {
	map<string, Value> cache;
public:
	string get(string key);
	void set(string key, string value);
	void remove(string key);
};