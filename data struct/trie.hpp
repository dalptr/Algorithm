struct [[maybe_unused]] Trie {
    static constexpr char FIRST_LOWER_CASE = 'a';
    static constexpr size_t ALPHABET_SIZE = 26;
    struct Node {
        Node *children[ALPHABET_SIZE]{};
        bool is_word = false;
    };
    Node *root;

    Trie() {
        root = new Node();
    }

    [[maybe_unused]] void insert(const string &word) const {
        Node *node = root;
        for (char c: word) {
            if (node->children[c - FIRST_LOWER_CASE] == nullptr)
                node->children[c - FIRST_LOWER_CASE] = new Node();
            node = node->children[c - FIRST_LOWER_CASE];
        }
        node->is_word = true;

    }

    [[maybe_unused]] void erase(const string &word) const {
        Node *node = root;
        for (char c: word) {
            if (node->children[c - FIRST_LOWER_CASE] == nullptr) return;
            node = node->children[c - FIRST_LOWER_CASE];
        }
        node->is_word = false;
    }

    [[maybe_unused]] bool search(const string &word) const {
        Node *node = root;
        for (char c: word) {
            if (node->children[c - FIRST_LOWER_CASE] == nullptr) return false;
            node = node->children[c - FIRST_LOWER_CASE];
        }
        return node->is_word;
    }

    void dictionary(vector<string> &ans, Node *node, string &word) const {
        if (node == nullptr) return;
        if (node->is_word) ans.push_back(word);
        size_t index = 0;
        for (char c = FIRST_LOWER_CASE; c < FIRST_LOWER_CASE + ALPHABET_SIZE; c++, ++index) {
            word.push_back(c);
            dictionary(ans, node->children[index], word);
            word.pop_back();
        }
    }

    [[maybe_unused]] inline void dictionary(vector<string> &ans) const {
        string word;
        dictionary(ans, root, word);
    }

    [[maybe_unused]] bool starts_with(const string &prefix) const {
        Node *node = root;
        for (char c: prefix) {
            if (node->children[c - FIRST_LOWER_CASE] == nullptr) return false;
            node = node->children[c - FIRST_LOWER_CASE];
        }
        return true;
    }

    int count(Node *node) const {
        if (node == nullptr) return 0;
        int ans = node->is_word;
        for (auto &i: node->children) {
            ans += count(i);
        }
        return ans;
    }

    [[maybe_unused]] int count_prefix(const string &prefix) const {
        Node *node = root;
        for (char c: prefix) {
            if (node->children[c - FIRST_LOWER_CASE] == nullptr) return 0;
            node = node->children[c - FIRST_LOWER_CASE];
        }
        return count(node);
    }
};
