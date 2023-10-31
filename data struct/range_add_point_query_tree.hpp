template<typename T>
struct [[maybe_unused]] range_add_point_query_tree {
    int tree_n = 0;
    fenwick_tree<T> tree;

    explicit range_add_point_query_tree(int n = -1) {
        if (n >= 0)
            init(n);
    }

    void init(int n) {
        tree_n = n;
        tree.init(tree_n);
    }

    template<typename T_array>
    [[maybe_unused]] void build(const T_array &initial) {
        assert(int(initial.size()) == tree_n);
        vector<T> diffs(tree_n);

        for (int i = 0; i < tree_n; i++)
            diffs[i] = initial[i] - (i > 0 ? initial[i - 1] : 0);

        tree.build(diffs);
    }

    [[maybe_unused]] void update(int start, int end, const T &change) {
        assert(start <= end);
        if (start < tree_n) tree.update(max(start, 0), change);
        if (end < tree_n) tree.update(max(end, 0), -change);
    }

    [[maybe_unused]] T query(int index) const {
        assert(0 <= index && index < tree_n);
        return tree.query(index + 1);
    }
};
