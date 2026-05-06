#include "testlib.h"
#include <vector>
#include <queue>

using namespace std;

struct State {
    int x, y, parity; // parity = steps taken mod 2
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int T = inf.readInt(1, 50, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        long long n = inf.readLong(2LL, 24LL, "n");
        inf.readSpace();
        long long K = inf.readLong(1LL, 1000000000LL, "k");
        inf.readEoln();

        // Global property check:
        // Ensure that for this (n, K), the number of ways to reach some corner
        // within at most K moves does not overflow a 64-bit signed integer.
        //
        // The board is 2n x 2n, starting at (0,0).
        // Knight moves: 8 possibilities.
        //
        // We compute the exact number of walks up to min(K, 2 * n * 2 * n) moves
        // on a compressed state space that keeps track of:
        //   - board position (x,y)
        //   - parity of steps (0 or 1) to distinguish layers
        //
        // Since an exact worst-case mathematical bound is not given in the
        // statement, and the output is only modulo 1000007, we conservatively
        // assert that the count does not exceed 9e18 during this bounded
        // computation; this protects against tests violating any implied
        // "answer fits in signed 64-bit before modulo" assumption.

        int N = int(2 * n);
        int maxSteps = (int)min(K, (long long)(4 * n * n)); // safety cap

        // Knight moves
        const int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
        const int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};

        // DP[parity][x][y]: number of ways to reach (x,y) with this parity
        vector<vector<long long>> dp0(N, vector<long long>(N, 0));
        vector<vector<long long>> dp1(N, vector<long long>(N, 0));
        dp0[0][0] = 1;

        auto isCorner = [N](int x, int y) -> bool {
            return (x == 0 || x == N - 1) && (y == 0 || y == N - 1);
        };

        long long totalWays = 0;
        long long LIMIT = (long long)9e18;

        for (int step = 1; step <= maxSteps; ++step) {
            vector<vector<long long>> &cur = (step & 1) ? dp1 : dp0;
            vector<vector<long long>> &prev = (step & 1) ? dp0 : dp1;

            // reset current layer
            for (int i = 0; i < N; ++i)
                fill(cur[i].begin(), cur[i].end(), 0LL);

            for (int x = 0; x < N; ++x) {
                for (int y = 0; y < N; ++y) {
                    long long ways = prev[x][y];
                    if (!ways) continue;
                    for (int m = 0; m < 8; ++m) {
                        int nx = x + dx[m];
                        int ny = y + dy[m];
                        if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
                        cur[nx][ny] += ways;
                        ensuref(cur[nx][ny] >= 0 && cur[nx][ny] <= LIMIT,
                                "Number of ways overflow at cell (%d,%d) step %d for test %d",
                                nx, ny, step, tc + 1);
                    }
                }
            }

            // Accumulate ways to any corner up to step K (or maxSteps)
            for (int x = 0; x < N; ++x) {
                for (int y = 0; y < N; ++y) {
                    if (!isCorner(x, y)) continue;
                    long long ways = cur[x][y];
                    if (!ways) continue;
                    totalWays += ways;
                    ensuref(totalWays >= 0 && totalWays <= LIMIT,
                            "Total number of ways overflow at step %d for test %d",
                            step, tc + 1);
                }
            }
        }
    }

    inf.readEof();
}
