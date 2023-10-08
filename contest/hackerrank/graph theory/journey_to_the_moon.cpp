// https://www.hackerrank.com/challenges/journey-to-the-moon/problem?
#include <vector>
#include <iostream>
#include <unordered_map>
#include <cstdint>
#include <numeric>

std::vector<std::vector<int>> graph;
std::vector<int> country_members_list;
std::vector<bool> selected;
int current_country_members;

void dfs(int astronaut) {
    selected[astronaut] = true;
    ++current_country_members;
    for (int astronaut_of_same_country: graph[astronaut]) {
        if (selected[astronaut_of_same_country]) continue;
        dfs(astronaut_of_same_country);
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
    std::cin >> n >> n_pair;
    graph.resize(n);
    selected.resize(n, false);
    std::unordered_map<int, bool> mark_atstronauts;
    for (int i = 0; i < n_pair; ++i) {
        int u, v;
        std::cin >> u >> v;
        mark_atstronauts[u] = mark_atstronauts[v] = true;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    for (int atstronaut = 0; atstronaut < n; ++atstronaut) {
        if (!mark_atstronauts[atstronaut]) {
            country_members_list.push_back(1);
            selected[atstronaut] = true;
        }
    }
    for (int atstronaut = 0; atstronaut < n; ++atstronaut) {
        if (selected[atstronaut]) continue;
        current_country_members = 0;
        dfs(atstronaut);
        country_members_list.push_back(current_country_members);
    }
    int total_astronauts = std::accumulate(country_members_list.begin(), country_members_list.end(), 0);
    size_t ans = combination(total_astronauts, 2);
    for (int country_member: country_members_list)
        ans -= combination(country_member, 2);
    std::cout << ans;
}
