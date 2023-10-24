template<class T>
struct [[maybe_unused]] Point {
    T x, y;

    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}

    bool operator<(Point p) const { return tie(x, y) < tie(p.x, p.y); }

    bool operator==(Point p) const { return tie(x, y) == tie(p.x, p.y); }

    Point operator+(Point p) const { return Point(x + p.x, y + p.y); }

    Point operator-(Point p) const { return Point(x - p.x, y - p.y); }

    Point operator*(T d) const { return Point(x * d, y * d); }

    Point operator/(T d) const { return Point(x / d, y / d); }

    [[maybe_unused]] T dot(Point p) const { return x * p.x + y * p.y; }

    T cross(Point p) const { return x * p.y - y * p.x; }

    T cross(Point a, Point b) const { return (a - *this).cross(b - *this); }

    double dist() const { return sqrt((double) (x * x + y * y)); }

    [[maybe_unused]] double angle() const { return atan2(y, x); }

    Point unit() const { return *this / dist(); }

    Point perp() const { return Point(-y, x); }

    [[maybe_unused]] Point normal() const { return perp().unit(); }

    [[maybe_unused]] Point rotate(double a) const {
        return Point(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }

    friend ostream &operator<<(ostream &os, Point p) {
        return os << "(" << p.x << "," << p.y << ")";
    }
};
