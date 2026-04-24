#include "testlib.h"
#include <vector>
#include <set>
#include <limits>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read grid size N, M
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100, "M");
    inf.readEoln();

    // Read number of blocked roads K
    int K = inf.readInt(0, 50, "K");
    inf.readEoln();

    // Read each blocked road, ensure it's valid and no duplicates
    set<pair<pair<int,int>, pair<int,int>>> blocked;
    for (int i = 0; i < K; i++) {
        int a = inf.readInt(0, N, "a_i");
        inf.readSpace();
        int b = inf.readInt(0, M, "b_i");
        inf.readSpace();
        int c = inf.readInt(0, N, "c_i");
        inf.readSpace();
        int d = inf.readInt(0, M, "d_i");
        inf.readEoln();

        // Must be unit distance
        ensuref(abs(a - c) + abs(b - d) == 1,
                "Blocked road %d: endpoints (%d,%d) and (%d,%d) are not adjacent",
                i, a, b, c, d);

        // Normalize edge for undirected uniqueness check
        pair<int,int> p1 = {a, b};
        pair<int,int> p2 = {c, d};
        if (p2 < p1) swap(p1, p2);

        ensuref(!blocked.count({p1, p2}),
                "Duplicate blocked road %d: (%d,%d)-(%d,%d)",
                i, a, b, c, d);
        blocked.insert({p1, p2});
    }

    // Compute number of shortest paths via DP, checking the 2^63-1 bound
    const __int128 MAXV = (__int128(1) << 63) - 1;
    vector<vector<__int128>> dp(N+1, vector<__int128>(M+1, 0));
    dp[0][0] = 1;
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= M; j++) {
            if (i == 0 && j == 0) continue;
            __int128 ways = 0;
            // From left cell (i-1, j) moving right
            if (i > 0) {
                pair<int,int> u = {i-1, j}, v = {i, j};
                if (u > v) swap(u, v);
                if (!blocked.count({u, v}))
                    ways += dp[i-1][j];
            }
            // From below cell (i, j-1) moving up
            if (j > 0) {
                pair<int,int> u = {i, j-1}, v = {i, j};
                if (u > v) swap(u, v);
                if (!blocked.count({u, v}))
                    ways += dp[i][j-1];
            }
            ensuref(ways <= MAXV,
                    "Number of paths exceeds 2^63-1 at cell (%d,%d)", i, j);
            dp[i][j] = ways;
        }
    }

    // Final answer fits in the specified bound by construction
    // and is non-negative by DP initialization.

    inf.readEof();
    return 0;
}
