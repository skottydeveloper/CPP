#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <random>
#include <cassert>
#include "BST.hpp"
#include "unit_tests.hpp"

int main() {
    Tester my_tester;

    for (int i = 0; i < 3; ++i) {
        my_tester.test_insert();
        my_tester.test_find();
        my_tester.test_min();
        my_tester.test_in_order();
    }

    return 0;
}