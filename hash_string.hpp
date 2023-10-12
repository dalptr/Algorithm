int64_t compute_hash(std::string const &s) {
    constexpr int p = 31;
    constexpr int m = 1e9 + 9;
    constexpr char MIN_CHAR = 'a';
    int64_t hash = 0;
    int64_t p_pow = 1;
    for (char c: s) {
        hash = (hash + (c - MIN_CHAR + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash;
}
