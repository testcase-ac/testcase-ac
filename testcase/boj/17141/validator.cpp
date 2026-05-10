#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N, M
    int N = inf.readInt(5, 50, "N");
    inf.readSpace();
    int M = inf.readInt(1, 10, "M");
    inf.readEoln();

    // 2. Read grid, and count number of 2's
    vector<vector<int>> grid(N, vector<int>(N));
    int cnt2 = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            grid[i][j] = inf.readInt(0, 2, format("grid[%d][%d]", i+1, j+1).c_str());
            if (j + 1 < N) inf.readSpace();
            else inf.readEoln();
            if (grid[i][j] == 2) ++cnt2;
        }
    }

    ensuref(cnt2 >= M, "Number of virus places (2's) is less than M: %d < %d", cnt2, M);
    ensuref(cnt2 <= 10, "Number of virus places (2's) is more than 10: %d", cnt2);

    inf.readEof();
}
