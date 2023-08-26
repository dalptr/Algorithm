#include <bits/stdc++.h>

struct __attribute__((unused)) FenwickTree {
    using type = long long;
    std::vector<type> bit;

    __attribute__((unused)) explicit FenwickTree(size_t size) {
        bit.resize(size + 1, 0);
    }

    __attribute__((unused)) void update(size_t pos, type val) {
        while (pos < bit.size()) {
            bit[pos] += val;
            pos += pos & -pos;
        }
    }

    __attribute__((unused)) type query(type pos) {
        type sum = 0;
        while (pos > 0) {
            sum += bit[pos];
            pos -= pos & -pos;
        }
        return sum;
    }
};
