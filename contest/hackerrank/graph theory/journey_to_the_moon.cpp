#include <bits/stdc++.h>

using namespace std;
vector<vector<int>> graph;
vector<int> country_members_list;
vector<bool> selected;
int current_country_members;
constexpr int MAX_N = int(1e5);

void dfs(int astronaut) {
    selected[astronaut] = true;
    ++current_country_members;
    for (int astronaut_from_same_country: graph[astronaut]) {
        if (selected[astronaut_from_same_country]) continue;
        dfs(astronaut_from_same_country);
    }
}

int64_t combination(int a, int b) {
    if (b < 0 || b > a) return 0;
    if (b > a / 2) b = a - b;
    int64_t ans = 1, product = 1;
    for (int i = 0; i < b; ++i)
        ans *= a - i;
    for (int i = 1; i <= b; ++i)
        product *= i;
    return ans / product;
}

int main() {
    int n, n_pair;
    cin >> n >> n_pair;
    graph.resize(n);
    selected.resize(n, false);
    bitset<MAX_N> mark_astronauts;
    for (int i = 0; i < n_pair; ++i) {
        int u, v;
        cin >> u >> v;
        mark_astronauts[u] = mark_astronauts[v] = true;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    for (int astronaut = 0; astronaut < n; ++astronaut) {
        if (!mark_astronauts[astronaut]) {
            country_members_list.push_back(1);
            selected[astronaut] = true;
        }
        if (selected[astronaut]) continue;
        current_country_members = 0;
        dfs(astronaut);
        country_members_list.push_back(current_country_members);
    }
    int total_astronauts = accumulate(country_members_list.begin(), country_members_list.end(), 0);
    size_t ans = combination(total_astronauts, 2);
    for (int country_members: country_members_list)
        ans -= combination(country_members, 2);
    cout << ans;
}
