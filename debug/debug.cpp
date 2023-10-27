#include<bits/stdc++.h>

using namespace std;

#ifdef LOCAL

[[maybe_unused]] string to_string(char c) {
    const string char_bracket = "'";
    return char_bracket + c + char_bracket;
}

string to_string(const string &s) {
    constexpr char quote = '"';
    return quote + s + quote;
}

template<typename A, typename B>
string to_string(const pair<A, B> &p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

[[maybe_unused]] string to_string(bool value) {
    return (value ? "true" : "false");
}

template<typename T>
string to_string([[maybe_unused]] const T &vector) {
    bool first = true;
    string res = "{";
    for (const auto element: vector) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(element);
    }
    res += "}";
    return res;
}

[[maybe_unused]] string to_string(const char *s) {
    return to_string((string) s);
}

void dbg_out() { cerr << "]\n"; }

template<typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << to_string(H) << ' ';
    dbg_out(T...);
}

template<typename H, typename... Tail>
void debug(H, Tail... T) {
    cerr << "[ ";
    dbg_out(T...);
}

#define watch(...) cerr << "Line: " << __LINE__ << " [ "; cerr << #__VA_ARGS__ << " ] "; debug(__VA_ARGS__)

#else
#define watch(...)
#endif
