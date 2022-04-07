#ifndef MERGE_SORT_HPP
#define MERGE_SORT_HPP

#include <vector>
#include <iterator>
#include <algorithm>

using vec_it = std::vector<int>::iterator;

void merge(vec_it lo, vec_it mid, vec_it hi) {
    while (lo != mid && mid != hi) {
        auto iter = mid;
        lo = std::upper_bound(lo, mid, *mid);
        mid = std::upper_bound(mid, hi, *lo);
        std::rotate(lo, iter, mid);
    }
}

void merge_sort(vec_it it_begin, vec_it it_end) {
    auto && size = std::distance(it_begin, it_end);
    
    if (size < 2) {
        return;
    }

    auto && it_mid = it_begin + size / 2 + size % 2;
    merge_sort(it_begin, it_mid);
    merge_sort(it_mid, it_end);
    merge(it_begin, it_mid, it_end);
}

#endif