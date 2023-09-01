#ifndef HEAP_HPP
#define HEAP_HPP

#include <vector>
#include <algorithm>

class Heap {
private:
    std::vector<int> vec;
    unsigned num_elements = 0;

public:
    // Default constructor and destructor
    Heap() {
        vec.push_back(-1);
    }

    ~Heap(){}

    void insert(int key) {
        // Insert a new key into the heap.
        ++num_elements;
        vec.push_back(key);

        // Call swim() to swap key to the correct node in the tree (i.e., the right spot in the vector).
        swim(num_elements); // "num_elements" is the index of key in the vector.
    }

    void remove_min() {
        // Remove the minimum key in the heap and return the value.
        if (num_elements == 0) {
            std::cerr << "no elements in heap" << '\n';
            return;
        }

        vec[1] = vec[num_elements];
        vec.pop_back(); // Remove the last node.
        
        --num_elements;
        
        sink(); // Adjust the ordering.
    }

    int peek() {
        // Return the minimum key in the heap, but don't remove it.
        if (num_elements > 0) {
            return vec[1];
        } else {
            std::cerr << "no elements in heap" << '\n';
            return -1;
        }
    }

    // Function to return number of elements in the heap.
    unsigned size() {
        return num_elements;
    }

    void print() {
        for (unsigned i = 1; i <= num_elements; ++i) {
            std::cout << vec[i] << ' ';
        }

        std::cout << '\n';
    }

private:
    // Helper function to check if an index is valid. 
    bool is_valid(unsigned i) {
        return (i >= 1) && (i <= num_elements);
    }

    unsigned left_child(unsigned i) {
        return 2 * i;
    }

    unsigned right_child(unsigned i) {
        return 2 * i + 1;
    }

    unsigned parent(unsigned i) {
        return i >> 1; // "i >> 1" is equivalent to dividing by two and truncating the value.
    }
   
    void swim(unsigned i) {
        unsigned p = parent(i);
        while ((p > 0) && (vec[i] < vec[p])) {
            std::swap(vec[i],vec[p]);
            // Increment i and p.
            i = p;
            p = parent(i);
        }
    }

    void sink() {
        unsigned pos = 1;
        unsigned left = left_child(pos);
        
        while (is_valid(left)) {
            unsigned potential_switch = left;
            
            if (is_valid(left + 1) && vec[left] > vec[left + 1]) {
                ++potential_switch;
            }

            if (vec[pos] <= vec[potential_switch]) {
                break;
            }
            
            std::swap(vec[pos], vec[potential_switch]);
            pos = potential_switch;
            left = left_child(pos);
        }
    }
};

#endif