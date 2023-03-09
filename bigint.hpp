#include<bits/stdc++.h>

using namespace std;

constexpr int base = 1e9, base_digits = 9;
constexpr int negative = -1;
constexpr int positive = 1;
constexpr int prime_candidates[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};
struct INTEGER {
#ifndef DEVELOPMENT_MODE
#define assert(...)
#endif
#define all(x) begin(x), end(x)
#define sz(x) (x).size()
    using i64 = long long int;
    using u64 = unsigned long long int;
    using u32 = unsigned int;
private:

public:
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

    INTEGER(const string &s) {
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
            const u32 n = other.z.size();
            if ((sign == 1 && *this >= other) || (sign == -1 && *this <= other)) {
                for (u32 i = 0, carry = 0; i < n || carry; ++i) {
                    z[i] -= carry + (i < n ? other.z[i] : 0);
                    carry = z[i] < 0;
                    if (carry) z[i] += base;
                }
                trim();
            } else {
                *this = other - *this;
                this->sign = -this->sign;
            }
        } else {
            *this += -other;
        }
        return *this;
    }

    friend INTEGER operator-(INTEGER a, const INTEGER &b) {
        return a -= b;
    }

    INTEGER &operator*=(int v) {
        if (v < 0) sign = -sign, v = -v;
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

    INTEGER operator*(int v) const {
        return INTEGER(*this) *= v;
    }

    friend pair<INTEGER, INTEGER> div_mod(const INTEGER &a1, const INTEGER &b1) {
        int norm = base / (b1.z.back() + 1);
        INTEGER a = a1.abs() * norm, b = b1.abs() * norm, q, r; // make last element of b big
        q.z.resize(a.z.size());
        for (int i = a.z.size() - 1; i >= 0; --i) {
            r *= base;
            r += a.z[i];
            int s1 = (b.z.size() < r.z.size() ? r.z[b.z.size()] : 0);
            int s2 = (b.z.size() - 1 < r.z.size() ? r.z[b.z.size() - 1] : 0);
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

    INTEGER operator/(const INTEGER &v) const {
        return div_mod(*this, v).first;
    }

    INTEGER operator%(const INTEGER &v) const {
        return div_mod(*this, v).second;
    }

    INTEGER &operator/=(int v) {
        if (v < 0) sign = -sign, v = -v;
        for (int i = z.size() - 1, rem = 0; i >= 0; --i) {
            i64 cur = z[i] + rem * (i64) base;
            z[i] = cur / v;
            rem = cur % v;
        }
        trim();
        return *this;
    }

    INTEGER operator/(int v) const {
        return INTEGER(*this) /= v;
    }

    int operator%(int v) const {
        if (v < 0) v = -v;
        int m = 0;
        for (int i = z.size() - 1; i >= 0; --i) {
            m = (z[i] + m * (i64) base) % v;
        }
        return m * sign;
    }

    INTEGER &operator*=(const INTEGER &v) {
        return *this = *this * v;
    }

    INTEGER &operator/=(const INTEGER &v) {
        return *this = *this / v;
    }

    bool operator<(const INTEGER &v) const {
        if (sign != v.sign) {
            return sign < v.sign;
        }
        if (z.size() != v.z.size()) {
            return int(z.size()) * sign < int(v.z.size()) * v.sign;
        }
        for (int i = z.size() - 1; i >= 0; --i) {
            if (z[i] != v.z[i]) return z[i] * sign < v.z[i] * sign;
        }
        return false;
    }

    bool operator>(const INTEGER &v) const {
        return v < *this;
    }

    bool operator<=(const INTEGER &v) const {
        return !(v < *this);
    }

    bool operator>=(const INTEGER &v) const {
        return !(*this < v);
    }

    bool operator==(const INTEGER &v) const {
        return !(*this < v) && !(v < *this);
    }

    bool operator!=(const INTEGER &v) const {
        return *this < v || v < *this;
    }

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
        for (int i = z.size() - 1; i >= 0; --i) {
            res = res * base + z[i];
        }
        return res * sign;
    }

    friend INTEGER gcd(const INTEGER &a, const INTEGER &b) {
        return b.is_zero() ? a : gcd(b, a % b);
    }

    [[maybe_unused]] friend INTEGER lcm(const INTEGER &a, const INTEGER &b) {
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
        os << (v.z.empty() ? 0 : v.z.back());
        for (int i = v.z.size() - 2; i >= 0; --i) {
            os << setw(base_digits) << setfill('0') << v.z[i];
        }
        return os; // pad with zeroes
    }

    static vector<int> convert_base(const vector<int> &a, int old_digits, int new_digits) {
        vector<long long> p(max(old_digits, new_digits) + 1); // blocks of 10^{old} -> 10^{new}
        p[0] = 1;
        for (u64 i = 1; i < p.size(); ++i) {
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

    static vector<long long> karatsuba_multiple(const vector<i64> &a, const vector<i64> &b) {
        const int n = a.size();
        vector<long long> res(2 * n);
        if (n <= 32) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < (n); ++j) {
                    res[i + j] += a[i] * b[j];
                }
            }
            return res;
        }
        int k = n / 2;
        vector<long long> a1(begin(a), begin(a) + k), a2(k + all(a));
        vector<long long> b1(begin(b), begin(b) + k), b2(k + all(b));
        vector<long long> a1b1 = karatsuba_multiple(a1, b1), a2b2 = karatsuba_multiple(a2, b2);
        for (int i = 0; i < k; ++i) {
            a2[i] += a1[i], b2[i] += b1[i];
        }
        vector<long long> r = karatsuba_multiple(a2, b2);
        for (u64 i = 0; i < a1b1.size(); ++i) {
            r[i] -= a1b1[i];
        }
        for (u64 i = 0; i < a2b2.size(); ++i) {
            r[i] -= a2b2[i];
        }
        for (int i = (0); i < ((r).size()); ++i) {
            res[i + k] += r[i];
        }
        for (int i = (0); i < ((a1b1).size()); ++i) {
            res[i] += a1b1[i];
        }
        for (int i = (0); i < ((a2b2).size()); ++i) {
            res[i + n] += a2b2[i];
        }
        return res;
    }

    INTEGER operator*(const INTEGER &v) const {
        if (min(z.size(), v.z.size()) < 150) {
            return native_multiple(v);
        }
        INTEGER res;
        res.sign = sign * v.sign;
        vector<int> a6 = convert_base(this->z, base_digits, 6);
        vector<int> b6 = convert_base(v.z, base_digits, 6);
        vector<long long> a(all(a6)), b(all(b6));
        while (sz(a) < sz(b)) a.push_back(0);
        while (sz(b) < sz(a)) b.push_back(0);
        while (sz(a) & (sz(a) - 1)) a.push_back(0), b.push_back(0); // make size power of 2
        vector<long long> c = karatsuba_multiple(a, b);
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

    INTEGER native_multiple(const INTEGER &v) const {
        INTEGER res;
        res.sign = sign * v.sign;
        res.z.resize(z.size() + v.z.size());
        for (u64 i = 0; i < z.size(); ++i)
            if (z[i]) {
                i64 cur = 0;
                for (u64 j = 0; j < v.z.size() || cur; ++j) {
                    cur += res.z[i + j] + (i64) z[i] * (j < v.z.size() ? v.z[j] : 0);
                    res.z[i + j] = cur % base;
                    cur /= base;
                }
            }
        res.trim();
        return res;
    }

    [[maybe_unused]] INTEGER random(u32 digits) {
        string s;
        for (u32 i = 0; i < digits; ++i) {
            s += rand() % 10 + '0';
        }
        return INTEGER(s);
    }

    [[maybe_unused]] friend string to_string(const INTEGER &v) {
        stringstream ss;
        ss << v;
        string s;
        ss >> s;
        return s;
    }

    INTEGER power_modulo(int _base, INTEGER &exponent, INTEGER &modulo) {
        INTEGER a = _base;
        INTEGER result = 1;
        while (exponent != 0) {
            if (exponent % 2 == 1) {
                result *= a;
                result = result % modulo;
            }
            exponent = exponent / 2;
            a *= a;
            a = a % modulo;
        }
        return result;
    }

    [[maybe_unused]] bool is_prime() {
        if (*this < 2) return false;
        for (int prime: prime_candidates) {
            if (*this % prime == 0) return (*this == prime);
        }
        INTEGER r = *this - 1;
        int e = 0;
        while (r % 2 == 0) {
            r /= 2;
            ++e;
        }
        for (int prime: prime_candidates) {
            INTEGER x = power_modulo(prime, r, *this);
            cout << x << endl;
            for (int t = 0; t < e && x > 1; ++t) {
                INTEGER y = x * x;
                y = y % *this;
                if (y == 1 && x != *this - 1) return false;
                x = y;
            }
            if (x != 1) return false;
        }
        return true;
    }
};
