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

// Implementation of class "evictionFIFO"
size_t evictionFIFO::getSize() {
	return evictionQueue.size();
}

string evictionFIFO::getFrontElement() {
	return evictionQueue.front();
}

void evictionFIFO::updateEvictionQueue(string new_key) {
	if(!evictionQueue.empty())
		evict();
	evictionQueue.push(new_key);
}

void evictionFIFO::pushEntry(string key) {
	evictionQueue.push(key);
}

void evictionFIFO::evict() {
	evictionQueue.pop();
}

// Implementation of class "mapDB"
string MapDB::get(string key) {
	if (cache.count(key))
		return cache[key].getValue();
	else {
		string value = m_file.read(key);
		if (value != "\0") {
			Value newValue;
			newValue.setValue(value);
			if (evictionTable.getSize() < evictionTableSize) {
				evictionTable.pushEntry(key);
				cache[key] = newValue;
			}
			else {
				string key_to_remove = evictionTable.getFrontElement();
				remove(key_to_remove);
				evictionTable.updateEvictionQueue(key);
				cache[key] = newValue;
			}
		}
		return value;
	}		
}

void MapDB::set(string key, string value) {
	Value newValue;
	newValue.setAvailability(false);
	newValue.setValue(value);
	if (cache.count(key)) {
		Value retrieved_value = cache[key];
		if (retrieved_value.isAvailable()) {
			cache[key] = newValue;
			m_file.modify(key,value);
		}
	}
	else {
		if (evictionTable.getSize() == evictionTableSize) {
			string key_to_evict = evictionTable.getFrontElement();
			cache.erase(key_to_evict);
			evictionTable.updateEvictionQueue(key);
		}
		else
			evictionTable.pushEntry(key);
		cache.insert(pair <string, Value> (key, newValue));
		m_file.modify(key, value);
	}
	newValue.setAvailability(true);
}

void MapDB::remove(string key) {
	cache.erase(key);
	m_file.remove(key);
}
