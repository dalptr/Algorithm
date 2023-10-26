#include <map>
#include <iostream>

std::map<std::pair<int, int>, bool> is_obstacle;

int ans, board_size, n_obstacles;
int queen_r, queen_c;

int is_valid_position(int r, int c) {
    return (r <= board_size && r >= 1 && c <= board_size && c >= 1);
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

void move(direction direction) {
    int r = queen_r + direction.row_step;
    int c = queen_c + direction.col_step;
    while (is_valid_position(r, c)) {
        if (is_obstacle[{r, c}]) {
            break;
        }
        r += direction.row_step;
        c += direction.col_step;
        ++ans;
    }
}

int main() {
    std::cin >> board_size >> n_obstacles;
    std::cin >> queen_r >> queen_c;
    while (n_obstacles--) {
        int obstacle_r, obstacle_c;
        std::cin >> obstacle_r >> obstacle_c;
        is_obstacle[{obstacle_r, obstacle_c}] = true;
    }
    for (auto &direction: QUEEN_DIRECTIONS) {
        move(direction);
    }
    std::cout << ans;
    return 0;
}
