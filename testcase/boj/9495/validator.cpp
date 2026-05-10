#include "testlib.h"
#include <vector>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(3, 50, "N");
    inf.readEoln();

    vector<string> board(N);
    for (int i = 0; i < N; ++i) {
        // Read exactly N chars consisting of '.', 'o', 'x'
        board[i] = inf.readToken("[.ox]{1,50}", "row");
        inf.readEoln();
        ensuref((int)board[i].size() == N,
                "Row %d must have exactly N=%d characters, but has %d",
                i + 1, N, (int)board[i].size());
    }

    // Check global constraint: white stones ('o') are not adjacent (4-directionally)
    const int dr[4] = { -1, 1, 0, 0 };
    const int dc[4] = { 0, 0, -1, 1 };
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            if (board[r][c] != 'o') continue;
            for (int d = 0; d < 4; ++d) {
                int nr = r + dr[d];
                int nc = c + dc[d];
                if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
                ensuref(board[nr][nc] != 'o',
                        "White stones must not be adjacent: cells (%d,%d) and (%d,%d) are both 'o'",
                        r + 1, c + 1, nr + 1, nc + 1);
            }
        }
    }

    inf.readEof();
}
