using ll = long long;

ll count_primes(ll N) { // count_primes(1e13) == 346065536839
    if (N <= 1) return 0;
    int sq = (int) sqrt(N);
    vector<ll> big_ans((sq + 1) / 2), small_ans(sq + 1);
    for (int i = 1, end = sq + 1; i < end; ++i) {
        small_ans[i] = (i - 1) / 2;
    }
    for (int i = 0, end = big_ans.size(); i < end; ++i) {
        big_ans[i] = (N / (2 * i + 1) - 1) / 2;
    }

    vector<bool> skip(sq + 1);
    int prime_cnt = 0;
    for (int p = 3; p <= sq; p += 2)
        if (!skip[p]) { 
            for (int j = p; j <= sq; j += 2 * p) {
                skip[j] = true;
            }
            for (int j = 0, end = min((ll) big_ans.size(), (N / p / p + 1) / 2); j < end; ++j) {
                ll prod = (ll) (2 * j + 1) * p;
                big_ans[j] -= (prod > sq ? small_ans[(double) N / prod]
                                         : big_ans[prod / 2]) - prime_cnt;
            }
            for (int j = sq, q = sq / p; q >= p; --q)
                for (; j >= q * p; --j)
                    small_ans[j] -= small_ans[q] - prime_cnt;
            ++prime_cnt;
        }
    return big_ans[0] + 1;
}
