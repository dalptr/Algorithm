const uint64_t tests[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};

uint64_t pow_64(__uint128_t base, uint64_t exp, uint64_t modulo) {
    uint64_t res = 1;
    for (; exp; exp >>= 1, base = base * base % modulo) {
        if (exp & 1) {
            res = __uint128_t(res) * base % modulo;
        }
    }
    return res;
}

bool is_prime(uint64_t n) {
    if (n == 1) return false;
    for (uint64_t num: tests) {
        if (n % num == 0) return n == num;
    }
    uint64_t r = n - 1, x, y;
    int e = 0;
    while (~r & 1) {
        r >>= 1, ++e;
    }
    for (uint64_t num: tests) {
        x = pow_64(num, r, n);
        for (int t = 0; t < e && x > 1; ++t) {
            y = (__uint128_t) x * x % n;
            if (y == 1 && x != n - 1) return false;
            x = y;
        }
        if (x != 1) return false;
    }
    return true;
}
