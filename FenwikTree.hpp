struct FenwickTree {
    using type = long long;
    std::vector<type> bit;

    FenwickTree(size_t size) {
        bit.resize(size + 1, 0);
    }

    void update(size_t pos, type val) {
        while (pos < bit.size()) {
            bit[pos] += val;
            pos += pos & -pos;
        }
    }

    type query(type pos) {
        type sum = 0;
        while (pos > 0) {
            sum += bit[pos];
            pos -= pos & -pos;
        }
        return sum;
    }
};
