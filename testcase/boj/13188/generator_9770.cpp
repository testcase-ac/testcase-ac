#include "testlib.h"
using namespace std;

const int MAXN = 10;
const int MAXMASK = 1 << MAXN;

// dp[mask][last][dirIdx]
// dirIdx: 0 -> direction -1 (came from right), 1 -> 0 (no previous), 2 -> +1 (came from left)
long long dp[MAXMASK][MAXN][3];

long long countRoutes(int N, int cs, int cf) {
    int start = cs - 1;
    int finish = cf - 1;
    int fullMask = (1 << N) - 1;
    int limitMask = 1 << N;

    // reset dp
    for (int m = 0; m < limitMask; ++m)
        for (int i = 0; i < N; ++i)
            for (int d = 0; d < 3; ++d)
                dp[m][i][d] = 0;

    // starting position, no previous direction
    dp[1 << start][start][1] = 1;

    for (int mask = 0; mask < limitMask; ++mask) {
        for (int last = 0; last < N; ++last) {
            for (int dirIdx = 0; dirIdx < 3; ++dirIdx) {
                long long cur = dp[mask][last][dirIdx];
                if (!cur) continue;

                int dir = dirIdx - 1; // -1, 0, +1

                for (int nxt = 0; nxt < N; ++nxt) {
                    if (mask & (1 << nxt)) continue;
                    if (nxt == last) continue;

                    int step_dir = (nxt > last ? +1 : -1);

                    if (dir == 0) {
                        // first jump: any direction allowed
                        int ndIdx = step_dir + 1;
                        dp[mask | (1 << nxt)][nxt][ndIdx] += cur;
                    } else {
                        // must alternate direction
                        if (step_dir == -dir) {
                            int ndIdx = step_dir + 1;
                            dp[mask | (1 << nxt)][nxt][ndIdx] += cur;
                        }
                    }
                }
            }
        }
    }

    long long ans = 0;
    for (int d = 0; d < 3; ++d)
        ans += dp[fullMask][finish][d];
    return ans;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N = 2, cs = 1, cf = 2;

    const int MAX_ATTEMPTS = 1000;
    bool found = false;

    for (int attempt = 0; attempt < MAX_ATTEMPTS && !found; ++attempt) {
        int scenario = rnd.next(0, 4);
        if (scenario == 0)      N = rnd.next(2, 3);
        else if (scenario == 1) N = rnd.next(4, 5);
        else if (scenario == 2) N = rnd.next(6, 7);
        else if (scenario == 3) N = rnd.next(8, 10);
        else                    N = rnd.next(2, 10);

        // Choose cs, cf with some structure for variability
        if (rnd.next(0, 1) == 0) {
            // Uniform random distinct
            do {
                cs = rnd.next(1, N);
                cf = rnd.next(1, N);
            } while (cs == cf);
        } else {
            int which = rnd.next(0, 3);
            if (which == 0) {
                cs = 1;
                cf = N;
            } else if (which == 1) {
                cs = N;
                cf = 1;
            } else {
                // Adjacent if possible
                if (N == 2) {
                    cs = 1;
                    cf = 2;
                } else {
                    cs = rnd.next(1, N - 1);
                    int dir = rnd.next(0, 1) ? 1 : -1;
                    cf = cs + dir;
                    if (cf < 1) cf = cs + 1;
                    if (cf > N) cf = cs - 1;
                }
            }
        }

        if (cs == cf) continue;
        if (countRoutes(N, cs, cf) > 0) {
            found = true;
        }
    }

    if (!found) {
        // Safe fallback known to have at least one route
        N = 2;
        cs = 1;
        cf = 2;
    }

    println(N, cs, cf);
    return 0;
}
