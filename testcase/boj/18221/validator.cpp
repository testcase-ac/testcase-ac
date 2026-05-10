#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(7, 1000, "N");
    inf.readEoln();

    // 2. Read the N x N grid, and check values
    vector<vector<int>> grid(N, vector<int>(N));
    int cnt_sungkyu = 0, cnt_prof = 0;
    int sungkyu_r = -1, sungkyu_c = -1;
    int prof_r = -1, prof_c = -1;

    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            grid[r][c] = inf.readInt(0, 5, "d");
            ensuref(grid[r][c] == 0 || grid[r][c] == 1 || grid[r][c] == 2 || grid[r][c] == 5,
                "Invalid value at (%d,%d): %d (must be 0, 1, 2, or 5)", r+1, c+1, grid[r][c]);
            if (grid[r][c] == 2) {
                cnt_sungkyu++;
                sungkyu_r = r;
                sungkyu_c = c;
            }
            if (grid[r][c] == 5) {
                cnt_prof++;
                prof_r = r;
                prof_c = c;
            }
            if (c < N-1) inf.readSpace();
        }
        inf.readEoln();
    }

    // 3. Check exactly one Sungkyu and one Professor, and not at same position
    ensuref(cnt_sungkyu == 1, "There must be exactly one Sungkyu (2), found %d", cnt_sungkyu);
    ensuref(cnt_prof == 1, "There must be exactly one Professor (5), found %d", cnt_prof);
    ensuref(!(sungkyu_r == prof_r && sungkyu_c == prof_c), "Sungkyu and Professor cannot be at the same position");

    inf.readEof();
}
