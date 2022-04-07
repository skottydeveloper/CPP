#include "hashmap.hpp"

using namespace std;

int main() {
	hashmap<string> map;
	
	map.add(5, "First"); // first attempt at positoin 5%5 = 0 successful.
	map.add(8, "Second"); // first attempt at positoin 8%5 = 3 successful.
	map.add(12, "Third"); // first attempt at positoin 12%5 = 2 successful.
	map.add(45, "Fourth"); // first attempt at 45%5 = 0 fails; then succeeds at the next positoin 0+1 = 1.
	map.add(2, "Fifth"); // first attempt at 2%5 = 2 fails, then fails at 3, and finally, succeeds at 4.
	map.add(24, "Sixth"); // first attempt at 24%5 fails; then all atempts to other positions fail because map is full.
	map.add(5, "Seventh"); // first attempt at 5%5=0. update the value of the key 5 into "Seventh".
	
	cout << boolalpha; // let cout print out true/false (rather than 1/0) for bools
	cout << "Is there something with key " << 5 << "? " << map.has_key(5) << endl;
	cout << "Is there something with key " << 8 << "? " << map.has_key(8) << endl;
	cout << "Is there something with key " << 24 << "? " << map.has_key(24) << endl;
	cout << "Is there something with key " << -46 << "? " << map.has_key(-46) << endl;
	
	cout << "Does it have a value " << "First" << "? " << map.has_value("First") << endl;
	cout << "Does it have a value " << "Second" << "? " << map.has_value("Second") << endl;
	cout << "Does it have a value " << "Third" << "? " << map.has_value("Third") << endl;
	cout << "Does it have a value " << "Fourth" << "? " << map.has_value("Fourth") << endl;
	
	cout << "What is the position of value " << "First" << "? " << map.get_key("First") << endl;
	cout << "What is the position of value " << "Second" << "? " << map.get_key("Second") << endl;
	cout << "What is the position of value " << "Third" << "? " << map.get_key("Third") << endl;
	cout << "What is the position of value " << "Fourth" << "? " << map.get_key("Fourth") << endl;
	
	cout << "Getting something with key " << 5 << "... We got " << map.get_value(5) << endl;
	cout << "Getting something with key " << 8 << "... We got " << map.get_value(8) << endl;
	cout << "Getting something with key " << 24 << "... We got " << map.get_value(24) << endl;
	cout << "Getting something with key " << -46 << "... We got " << map.get_value(-46) << endl;
}