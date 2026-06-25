#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "t");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        // CHECK: The statement calls h and w "width and height", but the
        // input format and official sample use h rows of length w.
        int h = inf.readInt(1, 100, "h");
        inf.readSpace();
        int w = inf.readInt(1, 100, "w");
        inf.readEoln();

        vector<string> board(h);
        for (int r = 0; r < h; ++r) {
            board[r] = inf.readLine("[.*1-9]{1,100}", "row");
            ensuref((int)board[r].size() == w,
                    "row %d has length %d, expected %d", r + 1,
                    (int)board[r].size(), w);
        }

        for (int r = 0; r < h; ++r) {
            for (int c = 0; c < w; ++c) {
                if (board[r][c] == '.') {
                    continue;
                }

                ensuref(c != 0 && c != w - 1,
                        "non-empty cell at row %d, side column %d", r + 1,
                        c + 1);

                // CHECK: The statement says no two obstacles or gates are
                // adjacent, but the official sample has an obstacle diagonally
                // adjacent to a gate. Enforce non-adjacency within each type.
                for (int dr = -1; dr <= 1; ++dr) {
                    for (int dc = -1; dc <= 1; ++dc) {
                        if (dr == 0 && dc == 0) {
                            continue;
                        }
                        int nr = r + dr;
                        int nc = c + dc;
                        if (nr < 0 || nr >= h || nc < 0 || nc >= w) {
                            continue;
                        }
                        ensuref(board[nr][nc] == '.' || board[nr][nc] != board[r][c],
                                "matching cells at (%d, %d) and (%d, %d) are adjacent",
                                r + 1, c + 1, nr + 1, nc + 1);
                    }
                }
            }
        }
    }

    inf.readEof();
}
