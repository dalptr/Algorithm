#include <map>
#include <iostream>

using namespace std;

map<pair<int, int>, bool> is_obstacle;

int ans, board_size, n_obstacles;
int queen_r, queen_c;

int is_valid_position(int r, int c) {
    return (r <= board_size && r >= 1 && c <= board_size && c >= 1);
}

void move(const int row_step, const int col_step) {
    int x = queen_r + row_step;
    int y = queen_c + col_step;
    while (is_valid_position(x, y)) {
        if (is_obstacle[{x, y}]) {
            break;
        }
        x += row_step;
        y += col_step;
        ++ans;
    }
}

struct direction {
    int row_step;
    int col_step;
};

constexpr direction QUEEN_DIRECTIONS[] = {
        {1,  0},
        {-1, 0},
        {0,  1},
        {0,  -1},
        {1,  1},
        {1,  -1},
        {-1, 1},
        {-1, -1}
};

int main() {
    cin >> board_size >> n_obstacles;
    cin >> queen_r >> queen_c;
    while (n_obstacles--) {
        int obstacle_r, obstacle_c;
        cin >> obstacle_r >> obstacle_c;
        is_obstacle[{obstacle_r, obstacle_c}] = true;
    }
    for (auto &direction: QUEEN_DIRECTIONS) {
        move(direction.row_step, direction.col_step);
    }
    cout << ans;
    return 0;
}
