#include "key_value_store.h"
#include "iostream"

int main() {
	MapDB store;
	store.set("Parika", "Goel");
	store.set("Praveen", "Ghanghas");
	std::cout << store.get("Praveen");
	getchar();
	return 0;
}