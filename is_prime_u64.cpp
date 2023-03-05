typedef uint64_t u64;
const u64 candidates[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};

u64 pow_64(__uint128_t base, u64 exp, u64 modulo) {
    u64 res = 1;
    for (; exp; exp >>= 1, base = base * base % modulo) {
        if (exp & 1) {
            res = __uint128_t(res) * base % modulo;
        }
    }
    return res;
}

bool is_prime(u64 n) {
    if (n == 1) return false;
    for (u64 candidate: candidates) {
        if (n % candidate == 0) return n == candidate;
    }
    u64 r = n - 1, x, y;
    int e = 0;
    while (~r & 1) {
        r >>= 1, ++e;
    }
    for (u64 candidate: candidates) {
        x = pow_64(candidate, r, n);
        for (int t = 0; t < e && x > 1; ++t) {
            y = (__uint128_t) x * x % n;
            if (y == 1 && x != n - 1) return false;
            x = y;
        }
        if (x != 1) return false;
    }
    return true;
}
