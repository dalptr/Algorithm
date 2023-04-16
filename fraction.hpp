#include <bits/stdc++.h>

struct fraction {
    using i64 = int64_t;

    static int compare(const fraction &a, const fraction &b) {
        __int128_t x = (__int128_t) a.numerator * b.denominator;
        __int128_t y = (__int128_t) b.numerator * a.denominator;
        return (int) (x - y);
    }

    i64 numerator, denominator;


    explicit fraction(i64 numerator, i64 denominator) {
        assert(denominator != 0);
        this->numerator = i64(numerator);
        this->denominator = i64(denominator);
        if (denominator < 0) {
            this->numerator = -this->numerator;
            this->denominator = -this->denominator;
        }
        reduce();
    }

    void reduce() {
        i64 gcd = std::__gcd(abs(numerator), denominator);
        numerator /= gcd;
        denominator /= gcd;
    }

    [[maybe_unused]]  bool is_integer() const {
        return (numerator % denominator == 0);
    }

    friend fraction operator+(const fraction &a, const fraction &b) {
        return fraction{a.numerator * b.denominator + b.numerator * a.denominator, a.denominator * b.denominator};
    }

    friend fraction operator-(const fraction &a, const fraction &b) {
        return fraction{a.numerator * b.denominator - b.numerator * a.denominator, a.denominator * b.denominator};
    }

    friend fraction operator*(const fraction &a, const fraction &b) {
        return fraction{a.numerator * b.numerator, a.denominator * b.denominator};
    }

    friend fraction operator/(const fraction &a, const fraction &b) {
        return fraction{a.numerator * b.denominator, a.denominator * b.numerator};
    }

    fraction &operator+=(const fraction &other) { return *this = *this + other; }

    fraction &operator-=(const fraction &other) { return *this = *this - other; }

    fraction &operator*=(const fraction &other) { return *this = *this * other; }

    fraction &operator/=(const fraction &other) { return *this = *this / other; }

    fraction &operator++() {
        numerator += denominator;
        return *this;
    }

    fraction &operator--() {
        numerator -= denominator;
        return *this;
    }

    fraction operator-() const {
        return fraction{-numerator, denominator};
    }

    bool operator==(const fraction &other) const { return compare(*this, other) == 0; }

    bool operator!=(const fraction &other) const { return compare(*this, other) != 0; }

    bool operator<(const fraction &other) const { return compare(*this, other) < 0; }

    bool operator>(const fraction &other) const { return compare(*this, other) > 0; }

    bool operator<=(const fraction &other) const { return compare(*this, other) <= 0; }

    bool operator>=(const fraction &other) const { return compare(*this, other) >= 0; }

    [[maybe_unused]]  double to_double() const {
        return (double) numerator / (double) denominator;
    }

    friend fraction abs(const fraction &f) {
        return fraction{abs(f.numerator), f.denominator};
    }

    friend std::ostream &operator<<(std::ostream &out, const fraction &frac) {
        return out << frac.numerator << '/' << frac.denominator;
    }
};
