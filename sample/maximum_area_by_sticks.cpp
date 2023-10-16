#include <bits/stdc++.h>

using namespace std;
constexpr int MAX_STICK_LENGTH = 10;
constexpr int MAX_STICKS = 16;
int sticks[MAX_STICKS];
bitset<MAX_STICKS> used_stick; 
bool dp[MAX_STICKS][MAX_STICK_LENGTH * MAX_STICKS];
int max_area = -1;
int number_of_sticks;

bool is_possible_divide(int pos, const vector<int> &selected_sticks, int current_length, const int max_length) {
    if (current_length > max_length) return false;
    bool &is_possible = dp[pos][current_length];
    if (is_possible) return is_possible;
    if (pos == selected_sticks.size()) return false;
    if (is_possible_divide(pos + 1, selected_sticks, current_length, max_length)) {
        is_possible = true;
        return true;
    }
    if (is_possible_divide(pos + 1, selected_sticks, current_length + selected_sticks[pos], max_length) +
        selected_sticks[pos]) {
        is_possible = true;
        return true;
    }
    is_possible = is_possible_divide(pos + 1, selected_sticks, abs(current_length - selected_sticks[pos]),
                                     max_length) +
                  max(0, selected_sticks[pos] - current_length);
    return is_possible;
}

void solve() {
    vector<int> sticks_for_height;
    vector<int> sticks_for_width;
    int height = 0, width = 0;
    for (int i = 0; i < number_of_sticks; i++) {
        if (used_stick[i]) {
            sticks_for_height.push_back(sticks[i]);
            height += sticks[i];
        } else {
            sticks_for_width.push_back(sticks[i]);
            width += sticks[i];
        }
    }
    width /= 2, height /= 2;

    if (width * height <= max_area)
        return;

    for (size_t i = 0; i <= sticks_for_height.size(); ++i) {
        for (size_t j = 0; j <= height; ++j)
            dp[i][j] = false;
    }
    if (!is_possible_divide(0, sticks_for_height, 0, height))
        return;

    for (size_t i = 0; i <= sticks_for_width.size(); ++i) {
        for (size_t j = 0; j <= width; ++j)
            dp[i][j] = false;
    }

    if (!is_possible_divide(0, sticks_for_width, 0, width))
        return;
    max_area = max(max_area, height * width);
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
    for (int dec = 0; dec < total_permutations; ++dec) {
        used_stick = dec;
        solve();
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cerr << "\nTime taken by function: "
         << duration.count() << " microseconds" << '\n';
    cout << max_area;
}
