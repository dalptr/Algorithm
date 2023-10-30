struct Trie {
    struct Node {
        Node *children[26]{};
        bool is_word = false;
    };
    Node *root;

    Trie() {
        root = new Node();
    }

    static constexpr char FIRST_LOWER_CASE = 'a';

    void insert(const string &word) const {
        Node *node = root;
        for (char c: word) {
            if (node->children[c - FIRST_LOWER_CASE] == nullptr)
                node->children[c - FIRST_LOWER_CASE] = new Node();
            node = node->children[c - FIRST_LOWER_CASE];
        }
        node->is_word = true;

    }

    void erase(const string &word) const {
        Node *node = root;
        for (char c: word) {
            if (node->children[c - FIRST_LOWER_CASE] == nullptr) return;
            node = node->children[c - FIRST_LOWER_CASE];
        }
        node->is_word = false;
    }

    bool search(const string &word) const {
        Node *node = root;
        for (char c: word) {
            if (node->children[c - FIRST_LOWER_CASE] == nullptr) return false;
            node = node->children[c - FIRST_LOWER_CASE];
        }
        return node->is_word;
    }

    bool starts_with(const string &prefix) const {
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

    int count_prefix(const string &prefix) const {
        Node *node = root;
        for (char c: prefix) {
            if (node->children[c - FIRST_LOWER_CASE] == nullptr) return 0;
            node = node->children[c - FIRST_LOWER_CASE];
        }
        return count(node);
    }
};
