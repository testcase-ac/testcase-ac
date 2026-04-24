#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N = 19;
    // Read board
    vector<vector<int>> board(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        vector<int> row = inf.readInts(N, 0, 2, "cell");
        inf.readEoln();
        for (int j = 0; j < N; j++) {
            board[i][j] = row[j];
        }
    }
    // After 19 lines, must be EOF
    // But first we validate global win conditions
    // Directions: right, down, diag-down-right, diag-up-right
    const int dx[4] = {0, 1, 1, -1};
    const int dy[4] = {1, 0, 1, 1};
    int wins[3] = {0, 0, 0};
    // For each cell and each direction, detect exactly five in a row
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int c = board[i][j];
            if (c == 0) continue;
            for (int d = 0; d < 4; d++) {
                int px = i - dx[d], py = j - dy[d];
                // Only start if previous cell is out of bounds or different color
                if (px >= 0 && px < N && py >= 0 && py < N && board[px][py] == c) 
                    continue;
                // Count length
                int len = 0;
                int x = i, y = j;
                while (x >= 0 && x < N && y >= 0 && y < N && board[x][y] == c) {
                    len++;
                    x += dx[d];
                    y += dy[d];
                }
                if (len == 5) {
                    wins[c]++;
                }
            }
        }
    }
    // Validate no color wins more than once
    ensuref(wins[1] <= 1, "Black (1) has %d winning lines (must be at most 1)", wins[1]);
    ensuref(wins[2] <= 1, "White (2) has %d winning lines (must be at most 1)", wins[2]);
    // Validate not both win
    ensuref(!(wins[1] == 1 && wins[2] == 1), "Both players win simultaneously");

    inf.readEof();
    return 0;
}
