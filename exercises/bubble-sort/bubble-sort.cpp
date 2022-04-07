#ifndef BUBBLE_HPP
#define BUBBLE_HPP

#include <vector>
#include <algorithm>

void bubble_sort(std::vector<int>& v) {
	bool swap = true;
    
	while (swap) {
        swap = false;

        for (size_t i = 0; i < v.size() - 1; i++) {
            if (v[i] > v[i + 1]) {
            	v[i] += v[i + 1];
                v[i + 1] = v[i] - v[i + 1];
                v[i] -= v[i + 1];
                swap = true;
            }
        }
	}	
}

#endif