#include <iostream>
#include <vector>
#include <algorithm>
#include "insertion_sort.hpp"

int main() {	
	std::vector<int> v {15, 4, 1, 3, 14, 7, 18, 9, 5, 6, 8, 17, 10, 2, 16, 13, 11, 12};
	
	insertion_sort(v);

	for (int x : v)
		std::cout << ' ' << x;
	std::cout << '\n';
}