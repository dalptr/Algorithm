struct LCA {
    int n = 0;
    vector<vector<int>> adj;
    vector<int> parent, depth, subtree_size;
    vector<int> euler, first_occurrence;
    vector<int> tour_start, tour_end;
    vector<int> tour_list, rev_tour_list;
    vector<int> heavy_root;
    vector<int> heavy_root_depth, heavy_root_parent;  // These two vectors serve purely to optimize get_kth_ancestor
    RMQ<int> rmq;
    bool built = false;

    explicit LCA(int _n = 0) {
        init(_n);
    }

    [[maybe_unused]] explicit LCA(const vector<vector<int>> &_adj) {
        init(_adj);
    }

    void init(int _n) {
        n = _n;
        adj.assign(n, {});
        parent.resize(n);
        depth.resize(n);
        subtree_size.resize(n);
        first_occurrence.resize(n);
        tour_start.resize(n);
        tour_end.resize(n);
        tour_list.resize(n);
        heavy_root.resize(n);
        built = false;
    }

    void init(const vector<vector<int>> &_adj) {
        init(int(_adj.size()));
        adj = _adj;
    }

    [[maybe_unused]] void add_edge(int a, int b) {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    [[maybe_unused]] int degree(int v) const {
        return int(adj[v].size()) + (built && parent[v] >= 0);
    }

    void dfs(int node, int par) {
        parent[node] = par;
        depth[node] = par < 0 ? 0 : depth[par] + 1;
        subtree_size[node] = 1;

        adj[node].erase(remove(adj[node].begin(), adj[node].end(), par), adj[node].end());

        for (int child: adj[node]) {
            dfs(child, node);
            subtree_size[node] += subtree_size[child];
        }

        // Heavy-light subtree reordering.
        sort(adj[node].begin(), adj[node].end(), [&](int a, int b) {
            return subtree_size[a] > subtree_size[b];
        });
    }

    int tour = 0;

    void tour_dfs(int node, bool heavy) {
        heavy_root[node] = heavy ? heavy_root[parent[node]] : node;
        first_occurrence[node] = int(euler.size());
        euler.push_back(node);
        tour_list[tour] = node;
        tour_start[node] = tour++;
        bool heavy_child = true;

        for (int child: adj[node]) {
            tour_dfs(child, heavy_child);
            euler.push_back(node);
            heavy_child = false;
        }

        tour_end[node] = tour;
    }

    [[maybe_unused]] void build(const vector<int> &roots = {}, bool build_rmq = true) {
        depth.assign(n, -1);

        for (int root: roots)
            if (depth[root] < 0)
                dfs(root, -1);

        for (int i = 0; i < n; i++)
            if (depth[i] < 0)
                dfs(i, -1);

        tour = 0;
        euler.clear();
        euler.reserve(2 * n);

        for (int i = 0; i < n; i++)
            if (parent[i] < 0) {
                tour_dfs(i, false);
                euler.push_back(-1);
            }

        assert(int(euler.size()) == 2 * n);
        vector<int> euler_depth;
        euler_depth.reserve(euler.size());

        for (int node: euler)
            euler_depth.push_back(node < 0 ? node : depth[node]);

        if (build_rmq)
            rmq.build(euler_depth);

        euler_depth.clear();
        heavy_root_depth.resize(n);
        heavy_root_parent.resize(n);

        for (int i = 0; i < n; i++) {
            heavy_root_depth[i] = depth[heavy_root[i]];
            heavy_root_parent[i] = parent[heavy_root[i]];
        }

        rev_tour_list = tour_list;
        reverse(rev_tour_list.begin(), rev_tour_list.end());
        built = true;
    }

    pair<int, array<int, 2>> get_diameter() const {
        assert(built);

        // We find the maximum of depth[u] - 2 * depth[x] + depth[v] where u, x, v occur in order in the Euler tour.
        pair<int, int> u_max = {-1, -1};
        pair<int, int> ux_max = {-1, -1};
        pair<int, array<int, 2>> uxv_max = {-1, {-1, -1}};

        for (int node: euler) {
            if (node < 0) break;
            u_max = max(u_max, {depth[node], node});
            ux_max = max(ux_max, {u_max.first - 2 * depth[node], u_max.second});
            uxv_max = max(uxv_max, {ux_max.first + depth[node], {ux_max.second, node}});
        }

        return uxv_max;
    }

    [[maybe_unused]] array<int, 2> get_center() const {
        pair<int, array<int, 2>> diam = get_diameter();
        int length = diam.first, a = diam.second[0], b = diam.second[1];
        return {get_kth_node_on_path(a, b, length / 2), get_kth_node_on_path(a, b, (length + 1) / 2)};
    }

    int get_lca(int a, int b) const {
        a = first_occurrence[a];
        b = first_occurrence[b];

        if (a > b)
            swap(a, b);

        return euler[rmq.query_index(a, b + 1)];
    }

    bool is_ancestor(int a, int b) const {
        return tour_start[a] <= tour_start[b] && tour_start[b] < tour_end[a];
    }

    [[maybe_unused]] bool on_path(int x, int a, int b) const {
        return (is_ancestor(x, a) || is_ancestor(x, b)) && is_ancestor(get_lca(a, b), x);
    }

    [[maybe_unused]] int get_dist(int a, int b) const {
        return depth[a] + depth[b] - 2 * depth[get_lca(a, b)];
    }

    // Returns the child of `a` that is an ancestor of `b`. Assumes `a` is a strict ancestor of `b`.
    [[maybe_unused]] int child_ancestor(int a, int b) const {
        assert(a != b && is_ancestor(a, b));
        int child = euler[rmq.query_index(first_occurrence[a], first_occurrence[b] + 1) + 1];
        return child;
    }

    int get_kth_ancestor(int a, int k) const {
        if (k > depth[a])
            return -1;

        int goal = depth[a] - k;

        while (heavy_root_depth[a] > goal)
            a = heavy_root_parent[a];

        return tour_list[tour_start[a] + goal - depth[a]];
    }

    int get_kth_node_on_path(int a, int b, int k) const {
        int anc = get_lca(a, b);
        int first_half = depth[a] - depth[anc];
        int second_half = depth[b] - depth[anc];

        if (k < 0 || k > first_half + second_half)
            return -1;

        if (k < first_half)
            return get_kth_ancestor(a, k);
        else
            return get_kth_ancestor(b, first_half + second_half - k);
    }

    [[maybe_unused]] int get_common_node(int a, int b, int c) const {
        int x = get_lca(a, b);
        int y = get_lca(b, c);
        int z = get_lca(c, a);
        return x ^ y ^ z;
    }

    [[maybe_unused]] vector<pair<int, int>> compress_tree(vector<int> nodes) const {
        if (nodes.empty())
            return {};

        auto compare_tour = [&](int a, int b) -> bool { return tour_start[a] < tour_start[b]; };
        sort(nodes.begin(), nodes.end(), compare_tour);
        int k = int(nodes.size());

        for (int i = 0; i < k - 1; i++)
            nodes.push_back(get_lca(nodes[i], nodes[i + 1]));

        sort(nodes.begin() + k, nodes.end(), compare_tour);
        inplace_merge(nodes.begin(), nodes.begin() + k, nodes.end(), compare_tour);
        nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
        vector<pair<int, int>> result = {{nodes[0], -1}};

        for (int i = 1; i < int(nodes.size()); i++)
            result.emplace_back(nodes[i], get_lca(nodes[i], nodes[i - 1]));

        return result;
    }
};

#define BUILD_SUBTREES 0

template<typename T>
struct [[maybe_unused]] tree_sum_DS {
    const LCA &lca;
    bool vertex_mode = false;
    vector<T> values;
    range_add_point_query_tree<T> path_tree;
    fenwick_tree<T> tour_tree;
    T tree_sum = T();
    
    [[maybe_unused]] explicit tree_sum_DS(const LCA &_lca) : lca(_lca) {}

    
    [[maybe_unused]] void init(bool _vertex_mode) {
        vertex_mode = _vertex_mode;
        values.assign(lca.n, T());
        path_tree.init(lca.n);
#ifdef BUILD_SUBTREES
        tour_tree.init(lca.n);
#endif
    }

    void update_node(int node, T change) {
        values[node] += change;
        tree_sum += change;
        path_tree.update(lca.tour_start[node], lca.tour_end[node], change);
#ifdef BUILD_SUBTREES
        tour_tree.update(lca.tour_start[node], change);
#endif
    }

    [[maybe_unused]] void update_edge(int a, int b, T change) {
        // Edge values are stored at the deeper node.
        if (lca.parent[a] == b)
            swap(a, b);

        assert(a == lca.parent[b]);
        update_node(b, change);
    }

    // Returns the sum of tree values for all nodes / edges on the path from `node` to the root, inclusive.
    T query_root_path(int node) const {
        return path_tree.query(lca.tour_start[node]);
    }

    // Returns the sum of tree values for all nodes / edges on the path from `u` to `v`, inclusive.
    [[maybe_unused]] T query_path(int u, int v, int anc = -1) const {
        if (anc < 0)
            anc = lca.get_lca(u, v);

        return query_root_path(u) + query_root_path(v) - 2 * query_root_path(anc) + (vertex_mode ? values[anc] : T());
    }

    // Returns the sum of tree values for all nodes / edges in the subtree of `node`, inclusive when in `vertex_mode`.
    [[maybe_unused]] T query_subtree(int node) const {
#ifdef BUILD_SUBTREES
        return tour_tree.query(lca.tour_start[node], lca.tour_end[node]) - (vertex_mode ? T() : values[node]);
#endif
    }
};
