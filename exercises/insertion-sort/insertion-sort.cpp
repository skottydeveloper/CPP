#ifndef INSERTION_HPP
#define INSERTION_HPP

#include <vector>
#include <algorithm>

void insertion_sort(std::vector<int>& v) {
	int i, j, tmp;

 	for (i = 1; i < v.size(); i++) {
    	j = i;
     	tmp = v[i];
     	
		while (j > 0 && tmp < v[j - 1]) {
        	v[j] = v[j - 1];
           	j--;
     	}
		v[j] = tmp;
	}	
}

#endif