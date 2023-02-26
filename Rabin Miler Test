using i64 = long long;
constexpr int accuracy = 20;

i64 random(i64 range) {
    return abs(rand()) % range;
}

i64 mul(i64 a, i64 b, i64 p) {
    a %= p;
    b %= p;
    i64 q = (i64) ((long double) a * b / p);
    i64 r = a * b - q * p;
    while (r < 0) r += p;
    while (r >= p) r -= p;
    return r;
}

i64 pow(i64 u, i64 v, i64 n) {
    i64 res = 1;
    while (v) {
        if (v & 1) res = mul(res, u, n);
        u = mul(u, u, n);
        v >>= 1;
    }
    return res;
}

bool rabin(i64 n) {
    if (n < 2) return false;
    if (n == 2) return true;
    i64 s = 0, m = n - 1;
    while (m % 2 == 0) {
        s++;
        m >>= 1;
    }
    for (int it = 0; it < accuracy; it++) {
        i64 u = random(n - 2) + 2;
        i64 f = pow(u, m, n);
        if (f == 1 || f == n - 1) continue;
        for (int i = 1; i < s; i++) {
            f = mul(f, f, n);
            if (f == 1) return false;
            if (f == n - 1) break;
        }
        if (f != n - 1) return false;
    }
    return true;
}
