template<class T>
struct [[maybe_unused]] point {
    T x, y;

    explicit point(T x = 0, T y = 0) : x(x), y(y) {}

    bool operator<(point p) const { return tie(x, y) < tie(p.x, p.y); }

    bool operator==(point p) const { return tie(x, y) == tie(p.x, p.y); }

    point operator+(point p) const { return point(x + p.x, y + p.y); }

    point operator-(point p) const { return point(x - p.x, y - p.y); }

    point operator*(T d) const { return point(x * d, y * d); }

    point operator/(T d) const { return point(x / d, y / d); }

    [[maybe_unused]] T dot(point p) const { return x * p.x + y * p.y; }

    T cross(point p) const { return x * p.y - y * p.x; }

    T cross(point a, point b) const { return (a - *this).cross(b - *this); }

    double dist() const { return sqrt((double) (x * x + y * y)); }

    [[maybe_unused]] double angle() const { return atan2(y, x); }

    point unit() const { return *this / dist(); }

    point perp() const { return point(-y, x); }

    [[maybe_unused]] point normal() const { return perp().unit(); }

    [[maybe_unused]] point rotate(double a) const {
        return point(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }

    friend std::ostream &operator<<(std::ostream &os, point p) {
        return os << "(" << p.x << "," << p.y << ")";
    }
};
