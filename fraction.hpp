#include <algorithm>
#include <cassert>
#include <iostream>

bool CHECK_OVERFLOW64 = true;

struct fraction {
    using ld = long double;

    static int cross_sign(const fraction &a, const fraction &b) {
        if (CHECK_OVERFLOW64) {
            ld double_value = (ld) a.numerator * b.denominator - (ld) b.numerator * a.denominator;
            if (abs(double_value) > 1e18)
                return double_value > 0 ? +1 : -1;
        }

        uint64_t uint64_value = (uint64_t) a.numerator * b.denominator - (uint64_t) b.numerator * a.denominator;
        auto actual = int64_t(uint64_value);
        return (actual > 0) - (actual < 0);
    }

    int64_t numerator, denominator;

    template<class A, class B>
    fraction(A numerator, B denominator) {
        assert(denominator != 0);
        this->numerator = int64_t(numerator);
        this->denominator = int64_t(denominator);
        swap_sign();
        reduce();
    }

    void swap_sign() {
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

    void reduce() {
        int64_t g = std::__gcd(abs(numerator), denominator);
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
