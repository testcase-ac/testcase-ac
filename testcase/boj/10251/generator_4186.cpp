#include "testlib.h"
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        int M = rnd.next(2, 8);
        int N = rnd.next(2, 8);
        int L = rnd.next(1, 10);

        // Generate hyper-biased edge weights
        vector<vector<int>> h(M, vector<int>(N-1));
        vector<vector<int>> v(M-1, vector<int>(N));
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N-1; j++) {
                if (rnd.next() < 0.3)
                    h[i][j] = rnd.wnext(1000, 3) + 1;   // bias to large
                else
                    h[i][j] = rnd.wnext(1000, -3) + 1;  // bias to small
            }
        }
        for (int i = 0; i < M-1; i++) {
            for (int j = 0; j < N; j++) {
                if (rnd.next() < 0.3)
                    v[i][j] = rnd.wnext(1000, 3) + 1;
                else
                    v[i][j] = rnd.wnext(1000, -3) + 1;
            }
        }

        // Compute minimal fuel by DP
        const int INF = numeric_limits<int>::max() / 2;
        vector<vector<int>> dp(M, vector<int>(N, INF));
        dp[0][0] = 0;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (j + 1 < N)
                    dp[i][j+1] = min(dp[i][j+1], dp[i][j] + h[i][j]);
                if (i + 1 < M)
                    dp[i+1][j] = min(dp[i+1][j], dp[i][j] + v[i][j]);
            }
        }
        int minFuel = dp[M-1][N-1];

        // Decide solvability
        bool solvable = (rnd.next() < 0.7);
        int G;
        if (solvable) {
            int slack = rnd.next(0, min(10, minFuel));
            G = minFuel + slack;
        } else {
            int dec = rnd.next(1, min(minFuel - 1, 10));
            G = minFuel - dec;
        }

        // Output test case
        println(M, N, L, G);
        for (int i = 0; i < M; i++) println(h[i]);
        for (int i = 0; i < M-1; i++) println(v[i]);
    }
    return 0;
}
