#include "key_value_store.h"

// Implementation of class "value"
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
	Value retrieved_value = cache[key];
	return retrieved_value.getValue();
}

void MapDB::set(string key, string value) {
	Value newValue;
	newValue.setAvailability(false);
	newValue.setValue(value);
	if (cache.count(key)) {
		Value retrieved_value = cache[key];
		if (retrieved_value.isAvailable()) {
			cache[key] = newValue;
		}
	}
	else {
		cache.insert(pair <string, Value> (key, newValue));
	}
	newValue.setAvailability(true);
}


