template<typename word>
struct prime_checker {
    static_assert(std::is_integral_v<word> && std::is_signed_v<word>,
                  "word must be a signed integral type");
    static_assert(sizeof(word) <= 8);

    template<typename T>
    using double_word_for = std::conditional_t<sizeof(T) == 2, int32_t,
            std::conditional_t<sizeof(T) == 4, int64_t,
                    std::conditional_t<sizeof(T) == 8, __int128_t, void>
            >
    >;

    using double_word = double_word_for<word>;

    static_assert(!std::is_void_v<double_word>,
                  "Unsupported word size");

    static constexpr std::size_t get_candidate_count() {
        return sizeof(word) == 2 ? 2 :
               sizeof(word) == 4 ? 3 :
               sizeof(word) == 8 ? 12 : 0;
    }

    static constexpr std::size_t num_candidates = get_candidate_count();

    static constexpr std::array<word, num_candidates> candidates = [] {
        if constexpr (sizeof(word) == 2) {
            return std::array<word, 2>{2, 3};
        } else if constexpr (sizeof(word) == 4) {
            return std::array<word, 3>{2, 7, 61};
        } else if constexpr (sizeof(word) == 8) {
            return std::array<word, 12>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
        } else {
            static_assert(sizeof(word) == 0, "Unsupported word size");
            return std::array<word, 0>{};
        }
        // reference: oeis.org/A014233
    }();

    static word power_modulo(double_word base, word exponent, word modulo) {
        double_word result = 1;
        while (exponent != 0) {
            if (exponent & 1) {
                result *= base;
                result %= modulo;
            }
            exponent >>= 1;
            base *= base;
            base %= modulo;
        }
        return static_cast<word>(result);
    }

    static bool is_prime(word n) {
        if (n < 2) return false;
        for (word candidate: candidates) {
            if (candidate % n == 0) return n == candidate;
        }
        word r = n - 1, x, y;
        int e = 0;
        while (r % 2 == 0) {
            r >>= 1, ++e;
        }
        for (word candidate: candidates) {
            x = power_modulo(candidate, r, n);
            for (int t = 0; t < e && x > 1; ++t) {
                y = power_modulo(x, 2, n);
                if (y == 1 && x != n - 1) return false;
                x = y;
            }
            if (x != 1) return false;
        }
        return true;
    }
};
