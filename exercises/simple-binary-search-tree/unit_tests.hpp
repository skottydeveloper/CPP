#ifndef UNIT_TESTS_HPP
#define UNIT_TESTS_HPP

#include <unordered_set>
#include <vector>
#include <random>
#include <cassert>
#include "BST.hpp"

class Tester {
public:
    std::vector<int> generate_without_duplicates() {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<unsigned> size_dist(1,20);
        unsigned size = size_dist(mt);
        std::vector<int> vec;
        vec.reserve(size);
        std::unordered_set<int> setto;
        std::uniform_int_distribution<int> val_dist(0,100);
        unsigned i = 0;

        while (i < size) {
            int val = val_dist(mt);

            if (setto.count(val) == 0) {
                setto.insert(val);
                vec.push_back(val);
                ++i;
            }
        }

        return vec;
    }

    void test_insert(void) {
        std::vector<int> vec = generate_without_duplicates();
        BST<int> tree;

        for (int x : vec) {
            tree.insert(x);
        }

        assert(vec.size() == tree.size());
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<unsigned> index_dist(0,vec.size()-1);
        
        for (int i = 0; i < 5; ++i) {
            unsigned index = index_dist(mt);
            tree.insert(vec[index]);
            assert(vec.size() == tree.size());
        }

        std::cout << "passed test_insert\n";
    }

    void test_find(void) {
        std::vector<int> vec = generate_without_duplicates();
        BST<int> tree;
        std::unordered_set<int> setto;

        for (int x : vec) {
            tree.insert(x);
            setto.insert(x);
        }

        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<unsigned> index_dist(0,vec.size()-1);
        
        for (int i = 0; i < 10; ++i) {
            unsigned index = index_dist(mt);
            BST<int>::Node* node = tree.find(vec[index]);
            assert(node != nullptr);
            assert(node->key == vec[index]);
        }

        std::uniform_int_distribution<int> val_dist(0,200);
        
        for (int i = 0; i < 20; ++i) {
            int val = val_dist(mt);
            
            if (setto.count(val) == 0) {
                BST<int>::Node* node = tree.find(val);
                assert(node == nullptr);
            }
        }

        std::cout << "passed test_find\n";
    }

    void test_min(void) {
        std::vector<int> vec = generate_without_duplicates();
        BST<int> tree;

        for (int x : vec) {
            tree.insert(x);
        }

        std::sort(vec.begin(), vec.end());
        BST<int>::Node* node = tree.min();
        assert(node != nullptr);
        assert(node->key == vec[0]);
        std::cout << "passed test_min\n";
    }

    void test_in_order() {
        std::vector<int> vec = generate_without_duplicates();
        BST<int> tree;

        for (int x : vec) {
            tree.insert(x);
        }

        std::sort(vec.begin(), vec.end());
        std::vector<int> in_order_vec = tree.make_vec();
        assert(vec.size() == in_order_vec.size());
        unsigned index = 0;
        
        for (int x : vec) {
            assert(in_order_vec[index++] == x);
        }
        
        std::cout << "passed test_in_order\n";
    }
};

#endif