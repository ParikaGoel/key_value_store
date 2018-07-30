#include "key_value_store.h"

// Implementation of class "Value"
bool Value::isAvailable() {
	return m_available;
}

string Value::getValue() {
	return m_str;
}

void Value::setValue(string new_str) {
	m_str = new_str;
}

void Value::setAvailability(bool avail) {
	m_available = avail;
}

//Implementation of class "mapDB"
string MapDB::get(string key) {
	Key entryKey(key);
	Value retrieved_value = cache[entryKey];
	return retrieved_value.getValue();
}

void MapDB::set(string key, string value) {
	Value newValue;
	newValue.setAvailability(false);
	newValue.setValue(value);
	Key entryKey(key);
	if (cache.count(entryKey)) {
		Value retrieved_value = cache[entryKey];
		if (retrieved_value.isAvailable()) {
			cache[entryKey] = newValue;
		}
	}
	else {
		cache.insert(pair <Key, Value> (entryKey, newValue));
	}
	newValue.setAvailability(true);
}

void MapDB::remove(string key) {
	Key entryKey(key);
	cache.erase(entryKey);
}
