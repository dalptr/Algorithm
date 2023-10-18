    void split(std::vector<std::string> &words, const std::string &text, char delimiter) {
        words.clear();
        std::string word;
        for (char c: text) {
            if (c == delimiter) {
                words.push_back(word);
                word.clear();
            } else {
                word.push_back(c);
            }
        }
        if (!word.empty()) {
            words.push_back(word);
        }
    }
