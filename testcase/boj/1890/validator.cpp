#include "testlib.h"
#include <vector>
#include <limits>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read board size
    int N = inf.readInt(4, 100, "N");
    inf.readEoln();

    // Read the board values
    vector<vector<int>> a(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        vector<int> row = inf.readInts(N, 0, 9, "cell");
        a[i] = row;
        inf.readEoln();
    }

    // The bottom‐right cell must be 0
    ensuref(a[N-1][N-1] == 0,
            "Bottom-right cell must be 0, but found %d",
            a[N-1][N-1]);

    // Compute number of paths via DP and check it stays within 2^63-1
    vector<vector<__int128>> dp(N, vector<__int128>(N, 0));
    dp[0][0] = 1;
    __int128 limit = (__int128)numeric_limits<long long>::max();

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (dp[i][j] == 0) continue;
            int d = a[i][j];
            if (d == 0) continue;
            int ni = i + d;
            if (ni < N) {
                dp[ni][j] += dp[i][j];
            }
            int nj = j + d;
            if (nj < N) {
                dp[i][nj] += dp[i][j];
            }
        }
    }

    __int128 ways = dp[N-1][N-1];
    ensuref(ways <= limit,
            "Number of paths exceeds 2^63-1");

    inf.readEof();
    return 0;
}
