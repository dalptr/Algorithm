#include <bits/stdc++.h>

#ifdef LOCAL

template<typename T>
std::string to_str(T t) {
    if constexpr (std::is_same_v<T, char>) {
        return "'" + std::string(1, t) + "'";
    } else if constexpr (std::is_same_v<T, std::string>) {
        return "\"" + t + "\"";
    } else if constexpr (std::is_same_v<T, bool>) {
        return t ? "true" : "false";
    } else if constexpr (std::is_same_v<T, const char *>) {
        return "\"" + std::string(t) + "\"";
    } else if constexpr (std::is_integral_v<T> ||
                         std::is_floating_point_v<T>) {
        return std::to_string(t);
    } else {
        static_assert(false, "Unsupported type");
        return ""; // avoid warning
    }
}

template<typename T, typename U>
std::string to_str(const std::pair<T, U> &p) {
    return "(" + to_str(p.first) + ", " + to_str(p.second) + ")";
}

template<typename T>
std::string to_str([[maybe_unused]] std::vector<T> &vec) {
    bool first = true;
    std::string res = "{";
    for (const auto &element: vec) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_str(element);
    }
    res += "}";
    return res;
}

void browser() { std::cerr << "]\n"; }

template<typename Head, typename... Tail>
void browser(Head H, Tail... T) {
    std::cerr << to_str(H) << ' ';
    browser(T...);
}

template<typename H, typename... Tail>
void watch(H val, Tail... T) {
    std::cerr << "[ ";
    browser(val, T...);
}

#define debug(...) std::cerr << "Line: " << __LINE__ << " [ "; std::cerr << #__VA_ARGS__ << " ] "; watch(__VA_ARGS__)

#else

#define debug(...)

#endif

int main() {
#ifdef LOCAL
    auto start = std::chrono::high_resolution_clock::now();
#endif
    
    

#ifdef LOCAL
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cerr << "Time: " << duration.count() << " microseconds" << '\n';
#endif
}
