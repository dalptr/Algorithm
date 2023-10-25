std::vector<int> smallest_factor;
std::vector<bool> is_prime;
std::vector<int> primes;

__attribute__((unused)) void sieve(int maximum) {
    maximum = std::max(maximum, 1);
    smallest_factor.assign(maximum + 1, 0);
    is_prime.assign(maximum + 1, true);
    is_prime[0] = is_prime[1] = false;
    primes = {};

    for (int i = 2; i <= maximum; i += 2) {
        is_prime[i] = i == 2;
        smallest_factor[i] = 2;
    }

    for (int p = 3; p * p <= maximum; p += 2)
        if (is_prime[p])
            for (int i = p * p; i <= maximum; i += 2 * p)
                if (is_prime[i]) {
                    is_prime[i] = false;
                    smallest_factor[i] = p;
                }

    if (maximum >= 2)
        primes.push_back(2);

    for (int p = 3; p <= maximum; p += 2)
        if (is_prime[p]) {
            smallest_factor[p] = p;
            primes.push_back(p);
        }
}
