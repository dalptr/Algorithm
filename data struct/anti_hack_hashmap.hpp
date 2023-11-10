struct hash_integer {
    static constexpr uint64_t C = uint64_t(2e18 * 3) + 71;
    static constexpr uint64_t RANDOM = 85858595959595959LL;

    size_t operator()(uint64_t x) const {
        return __builtin_bswap64((x ^ RANDOM) * C);
    }
};

template<class K, class V> using cmap = unordered_map<K, V, hash_integer>;
