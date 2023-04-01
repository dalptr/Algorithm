#include <bits/stdc++.h>

struct fraction {
    using i64 = int64_t;
    using i128 = __int128_t;
    using u128 = __uint128_t;

    static int cross_sign(const fraction &a, const fraction &b) {
        u128 x = ((__uint128_t) a.numerator * b.denominator) - ((u128) b.numerator * a.denominator);
        return int(((i128) x > 0) - ((i128) x < 0));
    }

    i64 numerator, denominator;

    template<class A, class B>
    fraction(A numerator, B denominator) {
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

    [[maybe_unused]] [[nodiscard]] bool is_integer() const {
        return (numerator % denominator == 0);
    }

    friend fraction operator+(const fraction &a, const fraction &b) {
        return {a.numerator * b.denominator + b.numerator * a.denominator, a.denominator * b.denominator};
    }

    friend fraction operator-(const fraction &a, const fraction &b) {
        return {a.numerator * b.denominator - b.numerator * a.denominator, a.denominator * b.denominator};
    }

    friend fraction operator*(const fraction &a, const fraction &b) {
        return {a.numerator * b.numerator, a.denominator * b.denominator};
    }

    friend fraction operator/(const fraction &a, const fraction &b) {
        return {a.numerator * b.denominator, a.denominator * b.numerator};
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
        return {-numerator, denominator};
    }

    bool operator==(const fraction &other) const { return cross_sign(*this, other) == 0; }

    bool operator!=(const fraction &other) const { return cross_sign(*this, other) != 0; }

    bool operator<(const fraction &other) const { return cross_sign(*this, other) < 0; }

    bool operator>(const fraction &other) const { return cross_sign(*this, other) > 0; }

    bool operator<=(const fraction &other) const { return cross_sign(*this, other) <= 0; }

    bool operator>=(const fraction &other) const { return cross_sign(*this, other) >= 0; }

    [[maybe_unused]] [[nodiscard]] double to_double() const {
        return (double) numerator / (double) denominator;
    }

    friend fraction abs(const fraction &f) {
        return {abs(f.numerator), f.denominator};
    }

    friend std::ostream &operator<<(std::ostream &out, const fraction &frac) {
        return out << frac.numerator << '/' << frac.denominator;
    }
};
