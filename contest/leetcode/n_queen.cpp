class Solution {
public:
    vector<vector<string>> ans;
    int val = -1;
    int n = -1;
    int *log2QueenPos = nullptr;

    static inline int fastLog2(int x) {
        return 31 - __builtin_clz(x);
    }

    void preprocess() {
        log2QueenPos = new int[size_t(pow(2, n)) + 1];
        log2QueenPos[0] = 1;
        for (int i = 1; i <= n; ++i) {
            log2QueenPos[i] = fastLog2(i);
        }
    }

    void solve(int row, int colMask, int leftDiagMask, int rightDiagMask, vector<string> &board) {
        if (row == n) {
            ans.push_back(board);
            return;
        }
        const int rowState = (colMask | leftDiagMask | rightDiagMask) & val;
        int safePos = rowState ^ val;
        while (safePos) {
            const int queenPos = safePos & (-safePos);
            safePos -= queenPos;
            if (!(queenPos & rowState)) {
                board[row][log2QueenPos[queenPos]] = 'Q';
                solve(row + 1, colMask |queenPos, (leftDiagMask | queenPos) << 1, (rightDiagMask | queenPos) >> 1,
                      board);
                board[row][log2QueenPos[queenPos]] = '.';
            }
        }
    }

    vector<vector<string>> solveNQueens(int n_) {
        n = n_;
        val = (1 << n) - 1;
        preprocess();
        vector<string> board(n, string(n, '.'));
        solve(0, 0, 0, 0, board);
        return ans;
    }
    // benchmark: 0.0 ms for <= 9
    // benchmark: 2.1 ms for 15
};
