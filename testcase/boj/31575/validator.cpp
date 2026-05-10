#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 300, "N");
    inf.readSpace();
    int M = inf.readInt(1, 300, "M");
    inf.readEoln();

    vector<vector<int>> a(M, vector<int>(N));

    for (int i = 0; i < M; ++i) {
        a[i] = inf.readInts(N, 0, 1, "cell");
        inf.readEoln();
    }

    // Check corners are 1
    ensuref(a[0][0] == 1, "Top-left cell must be 1");
    ensuref(a[M-1][N-1] == 1, "Bottom-right cell must be 1");

    // Check there exists a path from (0,0) to (M-1,N-1) moving only right or down
    vector<vector<bool>> dp(M, vector<bool>(N, false));
    if (a[0][0] == 1) dp[0][0] = true;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (a[i][j] == 0) continue;
            if (i > 0 && dp[i-1][j]) dp[i][j] = true;
            if (j > 0 && dp[i][j-1]) dp[i][j] = true;
        }
    }
    ensuref(dp[M-1][N-1],
            "There must exist a path from top-left to bottom-right using only right and down moves through cells with value 1");

    inf.readEof();
}
