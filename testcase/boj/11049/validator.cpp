#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 500, "N");
    inf.readEoln();

    vector<int> r(N), c(N);
    for (int i = 0; i < N; i++) {
        r[i] = inf.readInt(1, 500, "r_i");
        inf.readSpace();
        c[i] = inf.readInt(1, 500, "c_i");
        inf.readEoln();

        if (i > 0) {
            ensuref(c[i - 1] == r[i],
                    "matrix %d column count %d must equal matrix %d row count %d",
                    i, c[i - 1], i + 1, r[i]);
        }
    }

    const long long LIMIT = (1LL << 31) - 1;
    const long long INF = LIMIT + 1;

    vector<vector<long long>> worst(N, vector<long long>(N, 0));
    for (int len = 2; len <= N; ++len) {
        for (int left = 0; left + len <= N; ++left) {
            int right = left + len - 1;
            long long bestWorst = 0;
            for (int split = left; split < right; ++split) {
                long long cost = worst[left][split] + worst[split + 1][right] +
                                 1LL * r[left] * c[split] * c[right];
                bestWorst = max(bestWorst, min(cost, INF));
            }
            worst[left][right] = bestWorst;
        }
    }
    ensuref(worst[0][N - 1] <= LIMIT,
            "worst multiplication order cost %lld exceeds 2^31-1",
            worst[0][N - 1]);

    inf.readEof();
}
