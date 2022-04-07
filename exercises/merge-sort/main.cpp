#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "merge_sort.hpp"

// a helper function to print out a vector
void print (const std::vector<int>& v) {
    for(int x : v)
        std::cout << x << ' ';
    std::cout << '\n';
}  

// you can test your merge function with test_merge.
// it generates a random vector and randomly chooses an index "mid"
// in the middle of the vector.  Then it sorts the vector from 
// the beginning to mid and from mid to the end and calls your 
// merge function on the result.
void test_merge() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<unsigned> size_dist(1,20);
    unsigned size = size_dist(mt);
    std::vector<int> vec(size);
    std::uniform_int_distribution<int> val_dist(0,100);
    for (unsigned i = 0;i < size;++i)
        vec[i] = val_dist(mt);
    std::uniform_int_distribution<unsigned> index_dist(0,size-1);
    unsigned mid = index_dist(mt);
    std::sort(vec.begin(), vec.begin()+mid);
    std::sort(vec.begin()+mid, vec.end());
    std::cout << "testing merge on input\n";
    print(vec);
    merge(vec.begin(), vec.begin()+mid, vec.end());
    if (std::is_sorted(vec.begin(), vec.end()))
        std::cout << "passed\n";
    else
        std::cout << "BAD CASE\n";
}

// this function tests your merge_sort function
// Once your merge function is working, try this test too.
void test_sort() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<unsigned> size_dist(1,20);
    unsigned size = size_dist(mt);
    std::vector<int> vec(size);
    std::uniform_int_distribution<int> val_dist(0,100);
    for (unsigned i = 0;i < size;++i)
        vec[i] = val_dist(mt);
    std::cout << "testing sort on input\n";
    print(vec);
    merge_sort(vec.begin(), vec.end());
    if(std::is_sorted(vec.begin(), vec.end()))
        std::cout << "passed\n";
    else
        std::cout << "BAD CASE\n";
}

int main() {  
    for (int i=0; i < 5; ++i)
        test_merge(); // once your merge is working you can test the sorting function too.
    return 0;
}