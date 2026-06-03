#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(2, 1000, "M");
    inf.readEoln();

    vector<vector<int>> prefix(n + 1, vector<int>(m + 1, 0));
    for (int r = 1; r <= n; ++r) {
        for (int c = 1; c <= m; ++c) {
            int cell = inf.readInt(0, 1, "A_rc");
            prefix[r][c] = prefix[r - 1][c] + prefix[r][c - 1] -
                           prefix[r - 1][c - 1] + cell;
            if (c == m) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    int h = inf.readInt(1, n, "H");
    inf.readSpace();
    int w = inf.readInt(1, m, "W");
    inf.readSpace();
    int sr = inf.readInt(1, n - h + 1, "S_r");
    inf.readSpace();
    int sc = inf.readInt(1, m - w + 1, "S_c");
    inf.readSpace();
    int fr = inf.readInt(1, n - h + 1, "F_r");
    inf.readSpace();
    int fc = inf.readInt(1, m - w + 1, "F_c");
    inf.readEoln();

    int startWalls = prefix[sr + h - 1][sc + w - 1] -
                     prefix[sr - 1][sc + w - 1] -
                     prefix[sr + h - 1][sc - 1] + prefix[sr - 1][sc - 1];
    ensuref(startWalls == 0,
            "starting rectangle contains %d wall cells at top-left (%d, %d)",
            startWalls, sr, sc);

    inf.readEof();
}
