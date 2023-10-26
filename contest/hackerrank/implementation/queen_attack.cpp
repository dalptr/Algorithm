#include<map>
#include<iostream>

using namespace std;

map<pair<int, int>, bool> obstacles;

int ans, edge, n_obstacles;

int is_valid_position(int r, int c) {
    return (r <= edge && r > 0 && c <= edge && c > 0);
}

void move(int x, int y, int row_step, int col_step) {
    x += row_step;
    y += col_step;
    while (is_valid_position(x, y)) {
        if (obstacles[{x, y}]) {
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

constexpr direction directions[] = {
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
    cin >> edge >> n_obstacles;
    int queen_r, queen_c;
    cin >> queen_r >> queen_c;
    while (n_obstacles--) {
        int obstacle_r, obstacle_c;
        cin >> obstacle_r >> obstacle_c;
        obstacles[{obstacle_r, obstacle_c}] = true;
    }
    for (auto &direction: directions) {
        move(queen_r, queen_c, direction.row_step, direction.col_step);
    }
    cout << ans;
    return 0;
}
