#include <bits/stdc++.h>

using namespace std;
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i,0,a)
typedef int64_t i64;

#define tcT template<class T
tcT> using V = vector<T>;
using vi = V<int>;
using vl = V<i64>;

#define sz(x) int((x).size())
#define bg(x) begin(x)
#define all(x) bg(x), end(x)
#define bk back()
const int base = 1e9, base_digits = 9;

struct bigint {
    vi z;
    int sign;

    bigint() : sign(1) {}

    bigint(i64 v) {
        *this = v;
    }

    bigint &operator=(i64 v) {
        sign = v < 0 ? -1 : 1;
        v *= sign;
        z.clear();
        for (; v; v /= base) z.push_back(v % base);
        return *this;
    }

    bigint(const string &s) { read(s); }

    bigint &operator+=(const bigint &other) {
        //dbg("ADDING",*this,other,sign,other.sign);
        if (sign == other.sign) {
            for (int i = 0, carry = 0; i < sz(other.z) || carry; ++i) {
                if (i == sz(z)) z.push_back(0);
                z[i] += carry + (i < sz(other.z) ? other.z[i] : 0);
                carry = z[i] >= base;
                if (carry) z[i] -= base;
            }
        } else if (other != 0) *this -= -other;
        return *this;
    }

    friend bigint operator+(bigint a, const bigint &b) { return a += b; }

    bigint &operator-=(const bigint &other) {
        if (sign == other.sign) {
            if ((sign == 1 && *this >= other) || (sign == -1 && *this <= other)) {
                for (int i = 0, carry = 0; i < sz(other.z) || carry; ++i) {
                    z[i] -= carry + (i < sz(other.z) ? other.z[i] : 0);
                    carry = z[i] < 0;
                    if (carry) z[i] += base;
                }
                trim();
            } else { // result wii64 change sign
                *this = other - *this;
                this->sign = -this->sign;
            }
        } else *this += -other;
        return *this;
    }

    friend bigint operator-(bigint a, const bigint &b) { return a -= b; }

    bigint &operator*=(int v) {
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

    bigint operator*(int v) const { return bigint(*this) *= v; }

    friend pair<bigint, bigint> divmod(const bigint &a1, const bigint &b1) {
        int norm = base / (b1.z.bk + 1);
        bigint a = a1.abs() * norm, b = b1.abs() * norm, q, r; // make last element of b big
        q.z.resize(sz(a.z));
        R0F(i, sz(a.z)) {
            r *= base;
            r += a.z[i];
            int s1 = sz(b.z) < sz(r.z) ? r.z[sz(b.z)] : 0;
            int s2 = sz(b.z) - 1 < sz(r.z) ? r.z[sz(b.z) - 1] : 0;
            int d = ((i64) s1 * base + s2) / b.z.bk; // best approximation
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

    friend bigint sqrt(const bigint &a1) {
        bigint a = a1;
        while (!sz(a.z) || sz(a.z) & 1) a.z.push_back(0);
        int n = sz(a.z), firstDigit = ::sqrt((long double) a.z[n - 1] * base + a.z[n - 2]);
        int norm = base / (firstDigit + 1);
        a *= norm;
        a *= norm;
        while (!sz(a.z) || sz(a.z) & 1) a.z.push_back(0);
        bigint r = (i64) a.z[n - 1] * base + a.z[n - 2];
        firstDigit = (int) ::sqrt((long double) a.z[n - 1] * base + a.z[n - 2]);
        int q = firstDigit;
        bigint res;
        R0F(j, n / 2) {
            for (;; --q) {
                bigint r1 = (r - (res * 2 * base + q) * q) * base * base +
                            (j > 0 ? (i64) a.z[2 * j - 1] * base + a.z[2 * j - 2] : 0);
                if (r1 >= 0) {
                    r = r1;
                    break;
                }
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
        R0F(i, sz(z)) m = (z[i] + m * (i64) base) % v;
        return m * sign;
    }

    bigint &operator*=(const bigint &v) { return *this = *this * v; }

    bigint &operator/=(const bigint &v) { return *this = *this / v; }

    bool operator<(const bigint &v) const {
        if (sign != v.sign) return sign < v.sign;
        if (sz(z) != sz(v.z)) return sz(z) * sign < sz(v.z) * v.sign;
        R0F(i, sz(z)) if (z[i] != v.z[i]) return z[i] * sign < v.z[i] * sign;
        return 0; // equal
    }

    bool operator>(const bigint &v) const { return v < *this; }

    bool operator<=(const bigint &v) const { return !(v < *this); }

    bool operator>=(const bigint &v) const { return !(*this < v); }

    bool operator==(const bigint &v) const { return !(*this < v) && !(v < *this); }

    bool operator!=(const bigint &v) const { return *this < v || v < *this; }

    void trim() {
        while (sz(z) && z.bk == 0) z.pop_back();
        if (!sz(z)) sign = 1; // don't output -0
    }

    bool isZero() const { return !sz(z); }

    friend bigint operator-(bigint v) {
        if (sz(v.z)) v.sign = -v.sign;
        return v;
    }

    bigint abs() const { return sign == 1 ? *this : -*this; }

    i64 to_int64() const {
        i64 res = 0;
        R0F(i, sz(z)) res = res * base + z[i];
        return res * sign;
    }

    friend bigint gcd(const bigint &a, const bigint &b) {
        return b.isZero() ? a : gcd(b, a % b);
    }

    friend bigint lcm(const bigint &a, const bigint &b) {
        return a / gcd(a, b) * b;
    }

    void read(const string &s) {
        sign = 1;
        z.clear();
        int pos = 0;
        while (pos < sz(s) && (s[pos] == '-' || s[pos] == '+')) {
            if (s[pos] == '-') sign = -sign;
            ++pos;
        }
        for (int i = sz(s) - 1; i >= pos; i -= base_digits) {
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
        os << (!sz(v.z) ? 0 : v.z.bk);
        R0F(i, sz(v.z) - 1) os << setw(base_digits) << setfill('0') << v.z[i];
        return os;
    }

    static vi convert_base(const vi &a, int old_digits, int new_digits) {
        vl p(max(old_digits, new_digits) + 1); // blocks of 10^{old} -> 10^{new}
        p[0] = 1;
        for (int i = 1, end = sz(p); i < end; ++i) {
            p[i] = p[i - 1] * 10;
        }
        vi res;
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
        while (sz(res) && res.bk == 0) res.pop_back();
        return res;
    }

    static vl karatMul(const vl &a, const vl &b) { // karatsuba
        int n = sz(a);
        vl res(2 * n);
        if (n <= 32) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    res[i + j] += a[i] * b[j];
                }
            }
            return res;
        }
        int k = n / 2;
        vl a1(begin(a), begin(a) + k), a2(k + all(a));
        vl b1(begin(b), begin(b) + k), b2(k + all(b));
        vl a1b1 = karatMul(a1, b1), a2b2 = karatMul(a2, b2);
        for (int i = 0; i < k; ++i) {
            a2[i] += a1[i], b2[i] += b1[i];
        }
        vl r = karatMul(a2, b2);
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
        res.sign = sign * v.sign; // should work as long as # of digits isn't too large (> i64ONG_MAX/10^{12})
        vi a6 = convert_base(this->z, base_digits, 6); // blocks of 10^6 instead of 10^9
        vi b6 = convert_base(v.z, base_digits, 6);
        vl a(all(a6)), b(all(b6));
        while (sz(a) < sz(b)) a.push_back(0);
        while (sz(b) < sz(a)) b.push_back(0);
        while (sz(a) & (sz(a) - 1)) a.push_back(0), b.push_back(0); // make size power of 2
        vl c = karatMul(a, b);
        i64 cur = 0;
        for (int i = 0, end = sz(c); i < end; ++i) {
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

    friend string ts(const bigint &v) {
        stringstream ss;
        ss << v;
        string s;
        ss >> s;
        return s;
    }
};

bigint random_bigint(int n) {
    string s;
    for (int i = 0; i < n; ++i) {
        s += rand() % 10 + '0';
    }
    return bigint(s);
}
