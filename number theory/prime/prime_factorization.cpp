class PollardRho {
public:
    using i64 = long long;
    std::map<i64, int> ans;

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
        if (n < 2) return 0;
        if (n == 2) return 1;
        i64 s = 0, m = n - 1;
        while (m % 2 == 0) {
            s++;
            m >>= 1;
        }
        for (int it = 1; it <= 40; it++) {
            i64 u = random(n - 2) + 2;
            i64 f = pow(u, m, n);
            if (f == 1 || f == n - 1) continue;
            for (int i = 1; i < s; i++) {
                f = mul(f, f, n);
                if (f == 1) return 0;
                if (f == n - 1) break;
            }
            if (f != n - 1) return 0;
        }
        return 1;
    }

    i64 f(i64 x, i64 n) {
        return (mul(x, x, n) + 1) % n;
    }

    i64 find_factor(i64 n) {
        i64 x = random(n - 1) + 2;
        i64 y = x;
        i64 p = 1;
        while (p == 1) {
            x = f(x, n);
            y = f(f(y, n), n);
            p = std::__gcd(abs(x - y), n);
        }
        return p;
    }
    void native_factorize(int n){
        for (int i = 2; i * i <= n; i++) {
            while (n % i == 0) {
                ans[i]++;
                n /= i;
            }
        }
        if (n > 1) ans[n]++;
    }
    void factorize(i64 n) {
        if (n <= 1000000) {
            native_factorize(n);
            return;
        }
        if (rabin(n)) {
            ans[n]++;
            return;
        }
        i64 p = 0;
        while (p == 0 || p == n) {
            p = find_factor(n);
        }
        factorize(n / p);
        factorize(p);
    }
};
