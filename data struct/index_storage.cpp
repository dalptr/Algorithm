struct [[maybe_unused]] IndexStorage {
    static constexpr int MEMSET_VAL = 0x3f;
    static constexpr int DEFAULT_VALUE = 0x3f3f3f3f; 
    static constexpr int MAX_NUM = int(1e5);
    static constexpr int MIN_NUM = MAX_NUM * -1;
    static constexpr int BUFFER_SIZE = MAX_NUM * 2 + 1;
    int buffer[BUFFER_SIZE]; // using memset instead of default initialize

    static inline int get_unsigned_index(int index) {
        return index + MAX_NUM;
    }

    [[maybe_unused]] explicit IndexStorage(const std::vector<int> &numbers) {
        memset(buffer, MEMSET_VAL, sizeof(buffer));
        for (int i = 0, n = (int) numbers.size(); i < n; ++i) {
            buffer[get_unsigned_index(numbers[i])] = i;
        }
    }

    inline int operator[](int index) {
        if (index < MIN_NUM || index > MAX_NUM) return DEFAULT_VALUE;
        return buffer[get_unsigned_index(index)];
    }
};
