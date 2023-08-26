using ll = long long;
constexpr ll C = 6283185307179586631LL;
struct chash { // large odd number for C
    ll operator()(ll x) const { return __builtin_bswap64(x * C); }
};

__gnu_pbds::gp_hash_table<ll, int, chash> hash_table({}, {}, {}, {}, {1 << 16});
