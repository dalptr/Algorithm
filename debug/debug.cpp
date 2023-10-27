#include<bits/stdc++.h>

using namespace std;

#ifdef LOCAL
const string char_bracket = "'";

[[maybe_unused]] string to_string(char c) {
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

int _current_line = -1;
string _args;

string remove_conditional(const string &args) {
    auto pos = args.find(',') + 1;
    while (pos == ' ' && pos < args.size()) ++pos;
    return (pos == 0 ? "" : args.substr(pos + 1));
}

#define print_args()  cerr << "Line " << _current_line << ' ' ; cerr << ": (" << remove_conditional(_args) << "): ";

template<typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << to_string(H) << ' ';
    dbg_out(T...);
}

template<typename H, typename... Tail>
void debug(H conditional, Tail... T) {
    static_assert(std::is_same_v<H, bool>, "First argument of watch must be a boolean expression.");
    if (conditional) {
        print_args()
        cerr << "[ ";
        dbg_out(T...);
    }
}

#define watch(...) _current_line = __LINE__; _args = #__VA_ARGS__; debug(__VA_ARGS__)

#else
#define watch(...)
#endif

int main() {

}
