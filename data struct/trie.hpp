struct [[maybe_unused]] Trie {
    static constexpr char MIN_CHAR = 'a';

    struct Node {
        Node *child[26]{};
        int exist, cnt;

        Node() {
            exist = cnt = 0;
        }
    };

    Node *root;

    Trie() {
        root = new Node();
    };

    [[maybe_unused]] void add_string(std::string &s) const {
        Node *p = root;
        for (char c: s) {
            int index = c - MIN_CHAR;
            if (p->child[index] == nullptr) p->child[index] = new Node();
            p = p->child[index];
            p->cnt++;
        }
        p->exist++;
    }

    [[maybe_unused]] bool delete_string_recursive(Node *p, std::string &s, int i) {
        if (i != (int) s.size()) {
            int c = s[i] - MIN_CHAR;
            bool is_child_deleted = delete_string_recursive(p->child[c], s, i + 1);
            if (is_child_deleted) p->child[c] = nullptr;
        } else {
            p->exist--;
        }
        if (p != root) {
            p->cnt--;
            if (p->cnt == 0) {
                delete (p);
                return true;
            }
        }
        return false;
    }

    [[maybe_unused]] void delete_string(std::string s) {
        if (!find_string(s)) return;
        delete_string_recursive(root, s, 0);
    }

    [[maybe_unused]] bool find_string(std::string &s) const {
        Node *p = root;
        for (char c: s) {
            int index = c - MIN_CHAR;
            if (p->child[index] == nullptr) return false;
            p = p->child[index];
        }
        return (p->exist != 0);
    }

    [[maybe_unused]] int count_prefix(std::string &s) const {
        Node *p = root;
        for (char c: s) {
            int index = c - MIN_CHAR;
            if (p->child[index] == nullptr) return 0;
            p = p->child[index];
        }
        return p->cnt;
    }
};
