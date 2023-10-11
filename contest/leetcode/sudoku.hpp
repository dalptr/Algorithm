class Solution {
    static constexpr int edge = 9;
    static constexpr int to_board[edge][edge] = {
            {0, 0, 0, 1, 1, 1, 2, 2, 2},
            {0, 0, 0, 1, 1, 1, 2, 2, 2},
            {0, 0, 0, 1, 1, 1, 2, 2, 2},
            {3, 3, 3, 4, 4, 4, 5, 5, 5},
            {3, 3, 3, 4, 4, 4, 5, 5, 5},
            {3, 3, 3, 4, 4, 4, 5, 5, 5},
            {6, 6, 6, 7, 7, 7, 8, 8, 8},
            {6, 6, 6, 7, 7, 7, 8, 8, 8},
            {6, 6, 6, 7, 7, 7, 8, 8, 8}};
    static constexpr int all_available = (1 << 10) - 2;
    struct Board {
        int row[edge], column[edge], box[edge];
        bool unvisited[edge][edge];
        std::vector<std::vector<char>> *board;
    };

    static void add_to_board(Board &board, int value, int i, int j) {
        board.row[i] &= all_available ^ (1 << value);
        board.column[j] &= all_available ^ (1 << value);
        board.box[to_board[i][j]] &= all_available ^ (1 << value);
        (*board.board)[i][j] = char(value + '0');
        board.unvisited[i][j] = false;
    }

    static void remove_from_board(Board &board, int value, int i, int j) {
        board.row[i] |= (1 << value);
        board.column[j] |= (1 << value);
        board.box[to_board[i][j]] |= (1 << value);
        board.unvisited[i][j] = true;
        (*board.board)[i][j] = '0';
    }

    static int most_constrained(Board &board, int &i_opt, int &j_opt) {
        int non_empty_class = 0;
        int representative_row[10];
        int representative_col[10];
        for (int i = 0; i < edge; ++i)
            for (int j = 0; j < edge; ++j) {
                int available_nums = board.row[i] & board.column[j] & board.box[to_board[i][j]];
                int bit_count = __builtin_popcount(available_nums);
                representative_row[bit_count] =
                        board.unvisited[i][j] * i + (1 - board.unvisited[i][j]) * representative_row[bit_count];
                representative_col[bit_count] =
                        board.unvisited[i][j] * j + (1 - board.unvisited[i][j]) * representative_col[bit_count];
                non_empty_class |= board.unvisited[i][j] * (1 << bit_count);
            }

        int opt_class = __builtin_ffs(non_empty_class) - 1;
        if (opt_class >= 0) {
            i_opt = representative_row[opt_class];
            j_opt = representative_col[opt_class];
        }
        return opt_class;
    }

    bool recurse(Board &board) {
        int i, j;
        int flag = most_constrained(board, i, j);
        if (flag <= 0)
            return flag < 0;
        int available_nums_map = board.row[i] & board.column[j] & board.box[to_board[i][j]];
        int present_nums[edge];
        int free_spot = 0;
        for (int num = 1; num <= edge; ++num) {
            present_nums[free_spot] = num;
            free_spot += bool((1 << num) & (available_nums_map));
        }
        for (int idx = 0; idx < free_spot; ++idx) {
            int num = present_nums[idx];
            add_to_board(board, num, i, j);
            if (recurse(board))
                return true;
            remove_from_board(board, num, i, j);
        }
        return false;
    }

public:
    void solveSudoku(std::vector<std::vector<char>> &board) {
        Board board_map{};
        board_map.board = &board;
        for (int i = 0; i < edge; ++i) {
            board_map.row[i] = all_available;
            board_map.column[i] = all_available;
            board_map.box[i] = all_available;
        }
        for (int i = 0; i < edge; ++i)
            for (int j = 0; j < edge; ++j) {
                int value = board[i][j] - '0';
                value = value < 0 ? 0 : value;
                add_to_board(board_map, value, i, j);
                board_map.unvisited[i][j] = board[i][j] == '0';
            }
        for (int i = 0; i < edge; ++i) {
            board_map.row[i] &= all_available;
            board_map.column[i] &= all_available;
            board_map.box[i] &= all_available;
        }
        recurse(board_map);
    }
};
