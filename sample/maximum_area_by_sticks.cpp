#include <bits/stdc++.h>

using namespace std;
constexpr int MAX_STICK_LENGTH = 10;
constexpr int MAX_STICKS = 16;
int sticks[MAX_STICKS];
bitset<MAX_STICKS> used_stick;
int dp[MAX_STICKS][MAX_STICK_LENGTH * MAX_STICKS];
int ans = -1;
int number_of_sticks;

int calculate_possible_length(int pos, const vector<int> &selected_sticks, int current_length, const int max_length) {
    if (current_length > max_length / 2)
        return INT_MIN;
    int &res = dp[pos][current_length];
    if (res != -1)
        return res;
    if (pos == selected_sticks.size())
        return (current_length == 0 ? 0 : INT_MIN);
    int lhs = calculate_possible_length(pos + 1, selected_sticks, current_length, max_length);
    int rhs = calculate_possible_length(pos + 1, selected_sticks, current_length + selected_sticks[pos], max_length) +
              selected_sticks[pos];
    rhs = max(rhs,
              calculate_possible_length(pos + 1, selected_sticks, abs(current_length - selected_sticks[pos]),
                                        max_length) +
              max(0, selected_sticks[pos] - current_length));

    res = max(lhs, rhs);
    return res;
}

void solve() {
    vector<int> sticks_for_height;
    vector<int> sticks_for_width;
    int maximum_height = 0, maximum_width = 0;
    for (int i = 0; i < number_of_sticks; i++) {
        if (used_stick[i]) {
            sticks_for_height.push_back(sticks[i]);
            maximum_height += sticks[i];
        } else {
            sticks_for_width.push_back(sticks[i]);
            maximum_width += sticks[i];
        }
    }

    for (size_t i = 0; i <= sticks_for_height.size(); ++i) {
        for (size_t j = 0; j <= maximum_height; ++j)
            dp[i][j] = -1;
    }
    int possible_height = calculate_possible_length(0, sticks_for_height, 0, maximum_height);
    if (possible_height <= 0)
        return;

    for (size_t i = 0; i <= sticks_for_width.size(); ++i) {
        for (size_t j = 0; j <= maximum_width; ++j)
            dp[i][j] = -1;
    }

    int possible_width = calculate_possible_length(0, sticks_for_width, 0, maximum_width);
    if (possible_width <= 0)
        return;
    ans = max(ans, possible_height * possible_width);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> number_of_sticks;
    for (int i = 0; i < number_of_sticks; i++) {
        cin >> sticks[i];
    }
    auto start = chrono::high_resolution_clock::now();
    const int total_permutations = (1 << number_of_sticks);
    for (int mask = 0; mask < total_permutations; ++mask) {
        used_stick = mask;
        solve();
    }
    auto end = chrono::high_resolution_clock::now();
    // microseconds
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cerr << "\nTime taken by function: "
         << duration.count() << " microseconds" << '\n';
    cout << ans;
}
