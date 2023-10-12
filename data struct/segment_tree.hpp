#include <bits/stdc++.h>


struct segment_change {
    static constexpr int SENTINEL = std::numeric_limits<int>::lowest();
    int to_set, to_add;

    explicit segment_change(int _to_add = 0, int _to_set = SENTINEL) : to_set(_to_set), to_add(_to_add) {}

    [[nodiscard]] bool has_set() const {
        return to_set != SENTINEL;
    }

    [[nodiscard]] bool has_change() const {
        return has_set() || to_add != 0;
    }

    [[nodiscard]] segment_change combine(const segment_change &other) const {
        if (other.has_set())
            return other;
        return segment_change(to_add + other.to_add, to_set);
    }
};

struct segment {
    int maximum;
    int64_t sum;
    int first, last, max_diff;

    explicit segment(int _maximum = std::numeric_limits<int>::lowest(), int64_t _sum = 0, int _first = 0, int _last = 0,
                     int _max_diff = -1) : maximum(_maximum), sum(_sum), first(_first), last(_last),
                                           max_diff(_max_diff) {}

    [[nodiscard]] bool empty() const {
        return max_diff < 0;
    }

    void apply(int length, const segment_change &change) {
        if (change.has_set()) {
            maximum = change.to_set;
            sum = int64_t(length) * change.to_set;
            first = last = change.to_set;
            max_diff = 0;
        }
        maximum += change.to_add;
        sum += int64_t(length) * change.to_add;
        first += change.to_add;
        last += change.to_add;
    }

    void join(const segment &other) {
        if (empty()) {
            *this = other;
            return;
        } else if (other.empty()) {
            return;
        }
        maximum = std::max(maximum, other.maximum);
        sum += other.sum;
        max_diff = std::max({max_diff, other.max_diff, abs(last - other.first)});
        last = other.last;
    }

    void join(const segment &a, const segment &b) {
        *this = a;
        join(b);
    }
};

struct [[maybe_unused]] seg_tree {
    static int highest_bit(unsigned x) {
        return x == 0 ? -1 : 31 - __builtin_clz(x);
    }

    int tree_n = 0;
    std::vector<segment> tree;
    std::vector<segment_change> changes;

    explicit seg_tree(int n = -1) {
        if (n >= 0)
            init(n);
    }

    void init(int n) {
        tree_n = 1;
        while (tree_n < n)
            tree_n *= 2;
        tree.assign(2 * tree_n, segment());
        changes.assign(tree_n, segment_change());
    }

    [[maybe_unused]] void build(const std::vector<segment> &initial) {
        int n = int(initial.size());
        init(n);
        assert(n <= tree_n);
        for (int i = 0; i < n; i++)
            tree[tree_n + i] = initial[i];
        for (int position = tree_n - 1; position > 0; position--)
            tree[position].join(tree[2 * position], tree[2 * position + 1]);
    }

    void apply_and_combine(int position, int length, const segment_change &change) {
        tree[position].apply(length, change);
        if (position < tree_n)
            changes[position] = changes[position].combine(change);
    }

    void push_down(int position, int length) {
        if (changes[position].has_change()) {
            apply_and_combine(2 * position, length / 2, changes[position]);
            apply_and_combine(2 * position + 1, length / 2, changes[position]);
            changes[position] = segment_change();
        }
    }

    template<typename T_range_op>
    void process_range(int position, int start, int end, int a, int b, bool needs_join, T_range_op &&range_op) {
        if (a <= start && end <= b) {
            range_op(position, end - start);
            return;
        }
        if (position >= tree_n)
            return;
        push_down(position, end - start);
        int mid = (start + end) / 2;
        if (a < mid) process_range(2 * position, start, mid, a, b, needs_join, range_op);
        if (b > mid) process_range(2 * position + 1, mid, end, a, b, needs_join, range_op);
        if (needs_join) tree[position].join(tree[2 * position], tree[2 * position + 1]);
    }

    [[maybe_unused]] segment query(int a, int b) {
        assert(0 <= a && a <= b && b <= tree_n);
        segment answer;
        process_range(1, 0, tree_n, a, b, false, [&](int position, int) -> void {
            answer.join(tree[position]);
        });
        return answer;
    }

    [[maybe_unused]] [[nodiscard]] segment query_full() const {
        return tree[1];
    }

    [[maybe_unused]] void update(int a, int b, const segment_change &change) {
        assert(0 <= a && a <= b && b <= tree_n);
        process_range(1, 0, tree_n, a, b, true, [&](int position, int length) -> void {
            apply_and_combine(position, length, change);
        });
    }

    [[maybe_unused]] void update_single(int index, const segment &seg) {
        assert(0 <= index && index < tree_n);
        int position = tree_n + index;
        for (int up = highest_bit(tree_n); up > 0; up--)
            push_down(position >> up, 1 << up);
        tree[position] = seg;
        while (position > 1) {
            position /= 2;
            tree[position].join(tree[2 * position], tree[2 * position + 1]);
        }
    }

    [[maybe_unused]] std::vector<segment> to_array() {
        for (int i = 1; i < tree_n; i++)
            push_down(i, tree_n >> highest_bit(i));
        std::vector<segment> segments(tree_n);
        for (int i = 0; i < tree_n; i++)
            segments[i] = tree[tree_n + i];
        return segments;
    }
};


