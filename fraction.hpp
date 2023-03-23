#include <algorithm>
#include <cassert>
#include <iostream>

bool CHECK_OVERFLOW64 = true;

struct fraction {
    using ld = long double;
    using i64 = int64_t;
    using u64 = uint64_t;

    static int cross_sign(const fraction &a, const fraction &b) {
        if (CHECK_OVERFLOW64) {
            ld double_value = (ld) a.numerator * b.denominator - (ld) b.numerator * a.denominator;
            if (abs(double_value) > 1e18)
                return double_value > 0 ? +1 : -1;
        }

        u64 x = (u64) a.numerator * b.denominator - (u64) b.numerator * a.denominator;
        return int(((i64) x > 0) - ((i64) x < 0));
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
        i64 g = std::__gcd(abs(numerator), denominator);
        numerator /= g;
        denominator /= g;
    }

    [[maybe_unused]] [[nodiscard]] bool is_integer() const {
        return (denominator != 0 && numerator % denominator == 0);
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
