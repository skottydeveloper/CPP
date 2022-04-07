#include <bits/stdc++.h> 
using namespace std;

template <typename T>
class hashmap {
	private:
		const static size_t SIZE = 5; // the capacity of our map, i.e., the size of the array we use to hold <key, value> pairs.
		pair<int, T> map[SIZE]; // here, we implement a map using an array. Key type is std::int, value type is T.
		bool in_use[SIZE] {false}; // monitor the use of map: "true" means the array index is used; "false" means unused.
	
	public:
		int hash(const int&); // convert key into array index.
		void add(const int&, const T&); // insert a <key, value> pair to the map.
										// update the value if the key already exists in the map.
		T get_value(const int&); // get the value corresponding to a given key.
		int get_key(const T&); // get the key corresponding to a given value
							   // if multiple keys pair with the same value, return any of those keys.
		bool has_key(const int&); // check if a key exists in the map
		bool has_value(const T&); // check if a value exists in the map
};

template <typename T>
int hashmap<T> :: hash(const int& key) {
	return key % SIZE; // simple division function
}

template <typename T>
void hashmap<T> :: add (const int& key, const T& value) {
	auto array_index = hash(key); // get array index from the key
	// find the vacant spot for the <key, value> pair
	// if keep checking the next spot until
	// 	 1) an empty spot is found (in_use[array_index] == false), or
	//   2) an item in the map is found to have to same key (map[array_index].first == key), or
	//   3) have checked through all spots in the array (attempts == SIZE)
	int attempts = 0;

	while (in_use[array_index] && map[array_index].first != key && attempts < SIZE){
		array_index = (array_index+1) % SIZE; // the modulo operation allow us to use the array in a circular manner
		attempts++;
	}

	if (attempts < SIZE) { // if the spot at array_index is an empty spot or the existing item has the same key
		map[array_index] = {key, value}; // insert or update the pair at this index
		in_use[array_index] = true; // either case, this spot should be marked taken
		cout << "{" << key << ", " << value << "} added." << endl;
	} else { // the array is FULL, cannot add more elements to it
		cout << "Adding failed!" << endl;
	}
}

template <typename T>
T hashmap<T> :: get_value (const int& key) {
	auto array_index = hash(key); // get array index from the key
	// check the used spots in the array in a circular manner
	// starting from array_index has a chance of reducing the lookup time
	int attempts = 0;
	
	while (in_use[array_index] && attempts < SIZE){
		if (map[array_index].first == key){
			return map[array_index].second; // if find the key, return the corresponding value
		}
		array_index = (array_index + 1) % SIZE;
		attempts++;
	}
	return T(); // if not found, return an empty T object
}

template <typename T>
int hashmap<T> :: get_key(const T& value) {
	// We cannot apply the hash function to value, therefore,
	// we need to check the used spots from the begining to the end of the array.
	for (int i = 0; i < SIZE; ++i){
		if (in_use[i] && map[i].second == value){
			return map[i].first;
		}
	}
	
	return -1; // if not found, return -1
}

template <typename T>
bool hashmap<T> :: has_key(const int& key) {
	// this function is almost the same as the get_value() function
	// the only difference is that it returns true or false.
	
	auto array_index = hash(key);
	int attempts = 0;

	while (in_use[array_index] && attempts < SIZE) {
		if (map[array_index].first == key){
			return true;
		}
		array_index = (array_index + 1) % SIZE;
		attempts++;
	}
	
	return false;
}

template <typename T>
bool hashmap<T> :: has_value(const T& value) {
	// this function is almost the same as the get_key() function
	// the only difference is that it returns true or false.

	for (int i = 0; i < SIZE; ++i){
		if (in_use[i] && map[i].second == value){
			return true;
		}
	}
	
	return false;	
}