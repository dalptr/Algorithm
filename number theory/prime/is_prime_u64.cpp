typedef uint64_t u64;
typedef __uint128_t u128;
constexpr u64 candidates[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};

u64 power_modulo(u128 base, u64 exponent, u64 modulo) {
    u128 result = 1;
    while (exponent != 0) {
        if (exponent & 1) {
            result *= base;
            result %= modulo;
        }
        exponent >>= 1;
        base *= base;
        base %= modulo;
    }
    return result;
}

bool is_prime(u64 n) {
    if (n == 1) return false;
    for (u64 candidate: candidates) {
        if (n % candidate == 0) return n == candidate;
    }
    u64 r = n - 1, x, y;
    int e = 0;
    while (r % 2 == 0) {
        r >>= 1, ++e;
    }
    for (u64 candidate: candidates) {
        x = power_modulo(candidate, r, n);
        for (int t = 0; t < e && x > 1; ++t) {
            y = (u128) x * x % n;
            if (y == 1 && x != n - 1) return false;
            x = y;
        }
        if (x != 1) return false;
    }
    return true;
}
