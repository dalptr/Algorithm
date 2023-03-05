#include <bits/stdc++.h>

using namespace std;

typedef int64_t i64;
typedef uint64_t u64;
#define sz(x) int((x).size())
#define bg(x) begin(x)
#define all(x) bg(x), end(x)
const int base = 1e9, base_digits = 9;

struct bigint {
    vector<int> z;
    int sign;

    bigint() : sign(1) {}

    bigint(i64 v) {
        *this = v;
    }

    bigint &operator=(i64 v) { // verify
        sign = v < 0 ? -1 : 1;
        v *= sign;
        z.clear();
        while (v != 0) {
            z.push_back(v % base);
            v /= base;
        }
        return *this;
    }

    bigint(const string &s) { // verify
        read(s);
    }

    bigint &operator+=(const bigint &other) { // verify
        const int n = other.z.size();
        if (sign == other.sign) {
            for (int i = 0, carry = 0; i < n || carry; ++i) {
                if (i == z.size()) {
                    z.push_back(0);
                }
                z[i] += carry + (i < n ? other.z[i] : 0);
                carry = z[i] >= base;
                if (carry) {
                    z[i] -= base;
                }
            }
        } else if (other != 0) {
            *this -= -other;
        }
        return *this;
    }

    friend bigint operator+(bigint a, const bigint &b) { // verify
        return a += b;
    }

    bigint &operator-=(const bigint &other) {
        const int n = other.z.size();
        if (sign == other.sign) {
            if ((sign == 1 && *this >= other) || (sign == -1 && *this <= other)) {
                for (int i = 0, carry = 0; i < n || carry; ++i) {
                    z[i] -= carry + (i < n ? other.z[i] : 0);
                    carry = z[i] < 0;
                    if (carry) z[i] += base;
                }
                trim();
            } else {
                *this = other - *this;
                this->sign = -this->sign;
            }
        } else *this += -other;
        return *this;
    }

    friend bigint operator-(bigint a, const bigint &b) { // verify
        return a -= b;
    }

    bigint &operator*=(int v) { // verify
        if (v < 0) {
            sign = -sign, v = -v;
        }
        for (u64 i = 0, carry = 0; i < z.size() || carry; ++i) {
            if (i == z.size()) {
                z.push_back(0);
            }
            i64 cur = (i64) z[i] * v + carry;
            carry = cur / base;
            z[i] = cur % base;
        }
        trim();
        return *this;
    }

    bigint operator*(int v) const { return bigint(*this) *= v; }

    friend pair<bigint, bigint> divmod(const bigint &a1, const bigint &b1) {
        int norm = base / (b1.z.back() + 1);
        bigint a = a1.abs() * norm, b = b1.abs() * norm, q, r;
        q.z.resize(sz(a.z));
        for (u64 i = a.z.size() - 1; i >= 0; --i) {
            r *= base;
            r += a.z[i];
            int s1 = (b.z.size() < r.z.size() ? r.z[b.z.size()] : 0);
            int s2 = sz(b.z) - 1 < sz(r.z) ? r.z[sz(b.z) - 1] : 0;
            int d = ((i64) s1 * base + s2) / b.z.back();
            r -= b * d;
            while (r < 0) r += b, --d;
            q.z[i] = d;
        }
        q.sign = a1.sign * b1.sign;
        r.sign = a1.sign;
        q.trim();
        r.trim();
        return {q, r / norm};
    }

    [[maybe_unused]] friend bigint sqrt(const bigint &a1) {
        bigint a = a1;
        while (!sz(a.z) || sz(a.z) & 1) {
            a.z.push_back(0);
        }
        int n = sz(a.z), firstDigit = ::sqrt((long double) a.z[n - 1] * base + a.z[n - 2]);
        int norm = base / (firstDigit + 1);
        a *= norm;
        a *= norm;
        while (!sz(a.z) || sz(a.z) & 1) a.z.push_back(0);
        bigint r = (i64) a.z[n - 1] * base + a.z[n - 2];
        firstDigit = (int) ::sqrt((long double) a.z[n - 1] * base + a.z[n - 2]);
        int q = firstDigit;
        bigint res;
        for (int j = (n / 2) - 1; j >= 0; --j) {
            while (1) {
                bigint r1 = (r - (res * 2 * base + q) * q) * base * base +
                            (j > 0 ? (i64) a.z[2 * j - 1] * base + a.z[2 * j - 2] : 0);
                if (r1 >= 0) {
                    r = r1;
                    break;
                }
                --q;
            }
            res *= base;
            res += q;
            if (j > 0) {
                int d1 = sz(res.z) + 2 < sz(r.z) ? r.z[sz(res.z) + 2] : 0;
                int d2 = sz(res.z) + 1 < sz(r.z) ? r.z[sz(res.z) + 1] : 0;
                int d3 = sz(res.z) < sz(r.z) ? r.z[sz(res.z)] : 0;
                q = ((i64) d1 * base * base + (i64) d2 * base + d3) / (firstDigit * 2);
            }
        }
        res.trim();
        return res / norm;
    }

    bigint operator/(const bigint &v) const { return divmod(*this, v).first; }

    bigint operator%(const bigint &v) const { return divmod(*this, v).second; }

    bigint &operator/=(int v) {
        if (v < 0) sign = -sign, v = -v;
        for (int i = sz(z) - 1, rem = 0; i >= 0; --i) {
            i64 cur = z[i] + rem * (i64) base;
            z[i] = cur / v;
            rem = cur % v;
        }
        trim();
        return *this;
    }

    bigint operator/(int v) const { return bigint(*this) /= v; }

    int operator%(int v) const {
        if (v < 0) v = -v;
        int m = 0;
        for (u64 i = z.size() - 1; i >= 0; --i) {
            m = (z[i] + m * (i64) base) % v;
        }
        return m * sign;
    }

    bigint &operator*=(const bigint &v) { return *this = *this * v; }

    bigint &operator/=(const bigint &v) { return *this = *this / v; }

    bool operator<(const bigint &v) const {
        if (sign != v.sign) {
            return sign < v.sign;
        }
        if (z.size() != v.z.size()) {
            return (sign * z.size()) < (v.z.size() * v.sign);
        }
        for (u64 i = z.size() - 1; i >= 0; --i) {
            if (z[i] != v.z[i]) {
                return z[i] * sign < v.z[i] * sign;
            }
        }
        return 0;
    }

    bool operator>(const bigint &v) const { return v < *this; }

    bool operator<=(const bigint &v) const { return !(v < *this); }

    bool operator>=(const bigint &v) const { return !(*this < v); }

    bool operator==(const bigint &v) const { return !(*this < v) && !(v < *this); }

    bool operator!=(const bigint &v) const { return *this < v || v < *this; }

    void trim() {
        while (z.size() != 0 && z.back() == 0) {
            z.pop_back();
        }
        if (z.empty()) {
            sign = 1;
        }
    }

    bool isZero() const {
        return z.empty();
    }

    friend bigint operator-(bigint v) {
        if (sz(v.z)) v.sign = -v.sign;
        return v;
    }

    bigint abs() const { return sign == 1 ? *this : -*this; }

    [[maybe_unused]] i64 to_int64() const {
        i64 res = 0;
        for (u64 i = z.size() - 1; i >= (0); --i) {
            res = res * base + z[i];
        }
        return res * sign;
    }

    friend bigint gcd(const bigint &a, const bigint &b) {
        return b.isZero() ? a : gcd(b, a % b);
    }

    [[maybe_unused]] friend bigint lcm(const bigint &a, const bigint &b) {
        return a / gcd(a, b) * b;
    }

    void read(const string &s) {
        sign = 1;
        z.clear();
        int pos = 0;
        const int n = s.size();
        while (pos < n && (s[pos] == '-' || s[pos] == '+')) {
            if (s[pos] == '-') sign = -sign;
            ++pos;
        }
        for (int i = n - 1; i >= pos; i -= base_digits) {
            int x = 0;
            for (int j = max(pos, i - base_digits + 1); j <= i; j++)
                x = x * 10 + s[j] - '0';
            z.push_back(x);
        }
        trim();
    }

    friend istream &operator>>(istream &is, bigint &v) {
        string s;
        is >> s;
        v.read(s);
        return is;
    }

    friend ostream &operator<<(ostream &os, const bigint &v) {
        if (v.sign == -1) os << '-';
        os << (!sz(v.z) ? 0 : v.z.back());
        for (int i = v.z.size() - 1; i >= 0; --i) {
            os << setw(base_digits) << setfill('0') << v.z[i];
        }
        return os;
    }

    static vector<int> convert_base(const vector<int> &a, int old_digits, int new_digits) {
        vector<i64> p(max(old_digits, new_digits) + 1);
        p[0] = 1;
        for (int i = 1, end = p.size(); i < end; ++i) {
            p[i] = p[i - 1] * 10;
        }
        vector<int> res;
        i64 cur = 0;
        int cur_digits = 0;
        for (int v: a) {
            cur += v * p[cur_digits];
            cur_digits += old_digits;
            while (cur_digits >= new_digits) {
                res.push_back(cur % p[new_digits]);
                cur /= p[new_digits];
                cur_digits -= new_digits;
            }
        }
        res.push_back(cur);
        while (!res.empty() && res.back() == 0) {
            res.pop_back();
        }
        return res;
    }

    static vector<i64> karatMul(const vector<i64> &a, const vector<i64> &b) { // karatsuba
        const int n = a.size();
        vector<i64> res(2 * n);
        if (n <= 32) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    res[i + j] += a[i] * b[j];
                }
            }
            return res;
        }
        int k = n / 2;
        vector<i64> a1(begin(a), begin(a) + k), a2(k + all(a));
        vector<i64> b1(begin(b), begin(b) + k), b2(k + all(b));
        vector<i64> a1b1 = karatMul(a1, b1), a2b2 = karatMul(a2, b2);
        for (int i = 0; i < k; ++i) {
            a2[i] += a1[i], b2[i] += b1[i];
        }
        vector<i64> r = karatMul(a2, b2);
        for (int i = 0, end = sz(a1b1); i < end; ++i) {
            r[i] -= a1b1[i];
        }

        for (int i = 0, end = sz(a2b2); i < end; ++i) {
            r[i] -= a2b2[i];
        }
        for (int i = 0, end = sz(r); i < end; ++i) {
            res[i + k] += r[i];
        }
        for (int i = 0, end = sz(a1b1); i < end; ++i) {
            res[i] += a1b1[i];
        }
        for (int i = 0, end = sz(a2b2); i < end; ++i) {
            res[i + n] += a2b2[i];
        }
        return res;
    }

    bigint operator*(const bigint &v) const {
        if (min(sz(z), sz(v.z)) < 150) return mul_simple(v);
        bigint res;
        res.sign = sign * v.sign;
        vector<int> a6 = convert_base(this->z, base_digits, 6);
        vector<int> b6 = convert_base(v.z, base_digits, 6);
        vector<i64> a(all(a6)), b(all(b6));
        while (a.size() < b.size()) {
            a.push_back(0);
        }
        while (b.size() < a.size()) {
            b.push_back(0);
        }
        while (a.size() & (a.size() - 1)) {
            a.push_back(0), b.push_back(0);
        }
        const vector<i64> c = karatMul(a, b);
        i64 cur = 0;
        for (u64 i = 0, end = c.size(); i < end; ++i) {
            cur += c[i];
            res.z.push_back(cur % 1000000);
            cur /= 1000000;
        }
        res.z = convert_base(res.z, 6, base_digits);
        res.trim();
        return res;
    }

    bigint mul_simple(const bigint &v) const {
        bigint res;
        res.sign = sign * v.sign;
        res.z.resize(sz(z) + sz(v.z));
        for (int i = 0, end = sz(z); i < end; ++i) {
            if (z[i]) {
                i64 cur = 0;
                for (int j = 0; j < sz(v.z) || cur; ++j) {
                    cur += res.z[i + j] + (i64) z[i] * (j < sz(v.z) ? v.z[j] : 0);
                    res.z[i + j] = cur % base;
                    cur /= base;
                }
            }
        }
        res.trim();
        return res;
    }

    [[maybe_unused]] friend string ts(const bigint &v) {
        stringstream ss;
        ss << v;
        string s;
        ss >> s;
        return s;
    }

    void testStable() {
        u64 u64_t = 12345;
        bigint bigint1 = u64_t;
        assert(u64_t == bigint1.to_int64());
    }
};

bigint random_bigint(int n) {
    string s;
    for (int i = 0; i < n; ++i) {
        s += rand() % 10 + '0';
    }
    return bigint(s);
}

int main() {
    u64 q = 18393993939494;
    bigint t = q;
    t.testStable();
    cout << t;
}
