#include<bits/stdc++.h>

using namespace std;
using i64 = long long;
using u32 = unsigned int;
const int base = 1e9, base_digits = 9;
#define sz(x) (x).size()
#define all(x) begin(x), end(x)
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i,0,a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i,0,a)
constexpr int negative = -1;
constexpr int positive = 1;

struct INTEGER {
#ifndef DEVELOPMENT_MODE
#define assert(...)
#endif
    vector<int> z;
    int sign;

    INTEGER() : sign(1) {}

    INTEGER(i64 v) {
        *this = v;
    }

    INTEGER &operator=(i64 v) { // verify
        sign = (v < 0 ? negative : positive);
        v *= sign;
        z.clear();
        while (v != 0) {
            z.push_back(v % base);
            v /= base;
        }
        return *this;
    }

    INTEGER(const string &s) { // verify
        read(s);
    }

    INTEGER &operator+=(const INTEGER &other) {
        if (sign == other.sign) {
            const u32 n = other.z.size();
            for (u32 i = 0, carry = 0; i < n || carry; ++i) {
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

    friend INTEGER operator+(INTEGER a, const INTEGER &b) {
        return a += b;
    }

    INTEGER &operator-=(const INTEGER &other) {
        if (sign == other.sign) {
            if ((sign == 1 && *this >= other) || (sign == -1 && *this <= other)) {
                for (auto i = 0, carry = 0; i < sz(other.z) || carry; ++i) {
                    z[i] -= carry + (i < sz(other.z) ? other.z[i] : 0);
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

    friend INTEGER operator-(INTEGER a, const INTEGER &b) {
        return a -= b;
    }

    INTEGER &operator*=(int v) {
        if (v < 0) sign = -sign, v = -v;
        for (int i = 0, carry = 0; i < sz(z) || carry; ++i) {
            if (i == sz(z)) z.push_back(0);
            i64 cur = (i64) z[i] * v + carry;
            carry = cur / base;
            z[i] = cur % base;
        }
        trim();
        return *this;
    }

    INTEGER operator*(int v) const {
        return INTEGER(*this) *= v;
    }

    friend pair<INTEGER, INTEGER> div_mod(const INTEGER &a1, const INTEGER &b1) {
        int norm = base / (b1.z.back() + 1);
        INTEGER a = a1.abs() * norm, b = b1.abs() * norm, q, r; // make last element of b big
        q.z.resize(sz(a.z));
        R0F(i, sz(a.z)) {
            r *= base;
            r += a.z[i];
            int s1 = sz(b.z) < sz(r.z) ? r.z[sz(b.z)] : 0;
            int s2 = sz(b.z) - 1 < sz(r.z) ? r.z[sz(b.z) - 1] : 0;
            int d = ((i64) s1 * base + s2) / b.z.back(); // best approximation
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

    INTEGER operator/(const INTEGER &v) const { return div_mod(*this, v).first; }

    INTEGER operator%(const INTEGER &v) const { return div_mod(*this, v).second; }

    INTEGER &operator/=(int v) {
        if (v < 0) sign = -sign, v = -v;
        for (int i = sz(z) - 1, rem = 0; i >= 0; --i) {
            i64 cur = z[i] + rem * (i64) base;
            z[i] = cur / v;
            rem = cur % v;
        }
        trim();
        return *this;
    }

    INTEGER operator/(int v) const { return INTEGER(*this) /= v; }

    int operator%(int v) const {
        if (v < 0) v = -v;
        int m = 0;
        R0F(i, sz(z)) m = (z[i] + m * (i64) base) % v;
        return m * sign;
    }

    INTEGER &operator*=(const INTEGER &v) { return *this = *this * v; }

    INTEGER &operator/=(const INTEGER &v) { return *this = *this / v; }

    bool operator<(const INTEGER &v) const {
        if (sign != v.sign) return sign < v.sign;
        if (sz(z) != sz(v.z)) return sz(z) * sign < sz(v.z) * v.sign;
        R0F(i, sz(z)) if (z[i] != v.z[i]) return z[i] * sign < v.z[i] * sign;
        return 0; // equal
    }

    bool operator>(const INTEGER &v) const { return v < *this; }

    bool operator<=(const INTEGER &v) const { return !(v < *this); }

    bool operator>=(const INTEGER &v) const { return !(*this < v); }

    bool operator==(const INTEGER &v) const { return !(*this < v) && !(v < *this); }

    bool operator!=(const INTEGER &v) const { return *this < v || v < *this; }

    void trim() {
        while (!z.empty() && z.back() == 0) {
            z.pop_back();
        }
        if (z.empty()) sign = positive;
    }

    bool is_zero() const {
        return z.empty();
    }

    friend INTEGER operator-(INTEGER v) {
        if (!v.z.empty()) v.sign = -v.sign;
        return v;
    }

    INTEGER abs() const { return sign == 1 ? *this : -*this; }

    [[maybe_unused]] i64 to_long() const {
        i64 res = 0;
        R0F(i, sz(z)) res = res * base + z[i];
        return res * sign;
    }

    friend INTEGER gcd(const INTEGER &a, const INTEGER &b) {
        return b.is_zero() ? a : gcd(b, a % b);
    }

    friend INTEGER lcm(const INTEGER &a, const INTEGER &b) {
        return a / gcd(a, b) * b;
    }

    void read(const string &s) {
        sign = positive;
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

    friend istream &operator>>(istream &is, INTEGER &v) {
        string s;
        is >> s;
        v.read(s);
        return is;
    }

    friend ostream &operator<<(ostream &os, const INTEGER &v) {
        if (v.sign == -1) os << '-';
        os << (!sz(v.z) ? 0 : v.z.back());
        R0F(i, sz(v.z) - 1) os << setw(base_digits) << setfill('0') << v.z[i];
        return os; // pad with zeroes
    }

    static vector<int> convert_base(const vector<int> &a, int old_digits, int new_digits) {
        vector<long long> p(max(old_digits, new_digits) + 1); // blocks of 10^{old} -> 10^{new}
        p[0] = 1;
        FOR(i, 1, sz(p)) p[i] = p[i - 1] * 10;
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
        while (sz(res) && res.back() == 0) res.pop_back();
        return res;
    }

    static vector<long long> karatMul(const vector<long long> &a, const vector<long long> &b) { // karatsuba
        int n = sz(a);
        vector<long long> res(2 * n);
        if (n <= 32) {
            F0R(i, n) F0R(j, n) res[i + j] += a[i] * b[j];
            return res;
        }
        int k = n / 2;
        vector<long long> a1(begin(a), begin(a) + k), a2(k + all(a));
        vector<long long> b1(begin(b), begin(b) + k), b2(k + all(b));
        vector<long long> a1b1 = karatMul(a1, b1), a2b2 = karatMul(a2, b2);
        F0R(i, k) a2[i] += a1[i], b2[i] += b1[i];
        vector<long long> r = karatMul(a2, b2); // three instead of four products
        F0R(i, sz(a1b1)) r[i] -= a1b1[i];
        F0R(i, sz(a2b2)) r[i] -= a2b2[i];
        F0R(i, sz(r)) res[i + k] += r[i];
        F0R(i, sz(a1b1)) res[i] += a1b1[i];
        F0R(i, sz(a2b2)) res[i + n] += a2b2[i];
        return res;
    }

    INTEGER operator*(const INTEGER &v) const {
        if (min(sz(z), sz(v.z)) < 150) return mul_simple(v);
        INTEGER res;
        res.sign = sign * v.sign; // should work as long as # of digits isn't too large (> i64ONG_MAX/10^{12})
        vector<int> a6 = convert_base(this->z, base_digits, 6); // blocks of 10^6 instead of 10^9
        vector<int> b6 = convert_base(v.z, base_digits, 6);
        vector<long long> a(all(a6)), b(all(b6));
        while (sz(a) < sz(b)) a.push_back(0);
        while (sz(b) < sz(a)) b.push_back(0);
        while (sz(a) & (sz(a) - 1)) a.push_back(0), b.push_back(0); // make size power of 2
        vector<long long> c = karatMul(a, b);
        i64 cur = 0;
        for (auto i = 0; i < c.size(); ++i) { // process carries
            cur += c[i];
            res.z.push_back(cur % 1000000);
            cur /= 1000000;
        }
        res.z = convert_base(res.z, 6, base_digits);
        res.trim();
        return res;
    }

    INTEGER mul_simple(const INTEGER &v) const {
        INTEGER res;
        res.sign = sign * v.sign;
        res.z.resize(sz(z) + sz(v.z));
        F0R(i, sz(z)) if (z[i]) {
                i64 cur = 0;
                for (int j = 0; j < sz(v.z) || cur; ++j) {
                    cur += res.z[i + j] + (i64) z[i] * (j < sz(v.z) ? v.z[j] : 0);
                    res.z[i + j] = cur % base;
                    cur /= base;
                }
            }
        res.trim();
        return res;
    }

    friend string to_string(const INTEGER &v) {
        stringstream ss;
        ss << v;
        string s;
        ss >> s;
        return s;
    }
};

INTEGER random_INTERGER(int n) {
    string s;
    F0R(i, n) s += rand() % 10 + '0';
    return INTEGER(s);
}
