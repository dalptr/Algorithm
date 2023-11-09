#include <bits/stdc++.h>

using namespace std;

constexpr char RESERVED = '*';
constexpr int BOARD_SIZE = 8;

vector<vector<char>> chessboard(BOARD_SIZE, vector<char>(BOARD_SIZE));
int possible_ways = 0;

bool is_valid_place_for_queen(const vector<vector<bool>> &placed_queens, int row, int cell) {
    for (int r = row, c = cell; r >= 0 && c >= 0; --r, --c) {
        if (placed_queens[r][c]) {
            return false;
        }
    }
    for (int r = row, c = cell; r >= 0 && c < BOARD_SIZE; --r, ++c) {
        if (placed_queens[r][c]) {
            return false;
        }
    }
    return true;
}

void backtrack(vector<vector<bool>> &placed_queens, int r, vector<bool> &visited_cell, int queen_count) {
    if (queen_count == BOARD_SIZE) {
        ++possible_ways;
        return;
    }
    for (int c = 0; c < BOARD_SIZE; ++c) {
        if (visited_cell[c] || chessboard[r][c] == RESERVED) continue;
        if (!is_valid_place_for_queen(placed_queens, r, c)) continue;
        visited_cell[c] = true;
        placed_queens[r][c] = true;
        backtrack(placed_queens, r + 1, visited_cell, queen_count + 1);
        visited_cell[c] = false;
        placed_queens[r][c] = false;
    }
}

int main() {
    for (auto &row: chessboard) {
        for (char &square: row) {
            cin >> square;
        }
    }
    vector<vector<bool>> placed_queens(BOARD_SIZE, vector<bool>(BOARD_SIZE, false));
    vector<bool> visited_cell(BOARD_SIZE, false);
    backtrack(placed_queens, 0, visited_cell, 0);
    cout << possible_ways;
    return 0;
}
