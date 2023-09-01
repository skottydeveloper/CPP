#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "heap.hpp"

// Helper function to print out a vector.
void print(const std::vector<int>& v) {
    for (int x : v) {
        std::cout << x << ' ';
    }

    std::cout << '\n';
} 

// a function to help test your min heap implementation
// It creates a vector of size 16 filled with random entries,
// inserts the entries of the vector into your heap, and 
// then sequentially removes the minimum element until the heap
// is empty. It then checks that the elements come out in sorted order.
void test_heap() {
    const int size = 16;
    std::vector<int> tester(size);
    // This is the C++ to generate randomness from the <random> library
    // It is a bit more complicated than the C way rand() we used before
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> val_dist(0,100);
    // fill tester with random values
    for (unsigned i = 0; i < size; ++i) {
        tester[i] = val_dist(mt);
    }

    std::cout << "testing on input:\n";
    print(tester); 
    
    Heap h;
    // Insert the elements of tester into a min heap.
    for (int x : tester) {
        h.insert(x);
    }

    // h.print();
    std::cout << "the minimum key is " << h.peek() << '\n';

    // Sequentially pop the elements from heap, and put them into a new vector "sorted_output". 
    std::vector<int> sorted_output(size);
    for (unsigned i = 0; i < size; ++i) {
        sorted_output[i] = h.peek();
        h.remove_min();
    }

    if (is_sorted(sorted_output.begin(), sorted_output.end())) {
        std::cout << "passed\n";
    } else {
        std::cout << "BAD CASE\n";
    }
}

int main() {
    test_heap();
    
    return 0;
}