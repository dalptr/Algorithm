struct KMP {
    std::string pattern;
    std::vector<int> pi;

    void precompute() {
        pi.resize(pattern.size());
        for (int i = 1; i < pattern.size(); ++i) {
            int j = pi[i - 1];
            while (j > 0 && pattern[i] != pattern[j]) {
                j = pi[j - 1];
            }
            if (pattern[i] == pattern[j]) {
                ++j;
            }
            pi[i] = j;
        }
    }

    explicit KMP(std::string &pattern){
        this->pattern = pattern;
        precompute();
    }

    [[maybe_unused]] std::vector<int> match(const std::string &text) {
        std::vector<int> res;
        int j = 0;
        for (int i = 0; i < text.size(); ++i) {
            while (j > 0 && text[i] != pattern[j]) {
                j = pi[j - 1];
            }
            if (text[i] == pattern[j]) {
                ++j;
            }
            if (j == pattern.size()) {
                res.push_back(i - j + 1);
                j = pi[j - 1];
            }
        }
        return res;
    }

    [[maybe_unused]] int match_count(const std::string &text) {
        int ans = 0;
        int j = 0;
        for (char c: text) {
            while (j > 0 && c != pattern[j]) {
                j = pi[j - 1];
            }
            if (c == pattern[j]) {
                ++j;
            }
            if (j == pattern.size()) {
                ++ans;
                j = pi[j - 1];
            }
        }
        return ans;
    }
};
