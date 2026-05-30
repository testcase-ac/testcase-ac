#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(2, 300000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 1000, "K");
    inf.readEoln();

    const int MAXC = 100000;
    vector<int> X(N + 1), Y(N + 1), F(N + 1);
    set<pair<int, int>> coords;

    for (int i = 1; i <= N; i++) {
        X[i] = inf.readInt(0, MAXC, "X_i");
        inf.readSpace();
        Y[i] = inf.readInt(0, MAXC, "Y_i");
        inf.readSpace();
        F[i] = inf.readInt(0, 1000, "F_i");
        inf.readEoln();

        ensuref(coords.insert({X[i], Y[i]}).second,
                "duplicate coordinate at leaf %d: (%d, %d)", i, X[i], Y[i]);
    }

    vector<pair<int, int>> order;
    order.reserve(N);
    for (int i = 1; i <= N; i++) {
        order.emplace_back(X[i] + Y[i], i);
    }
    sort(order.begin(), order.end());

    const long long NEG_INF = LLONG_MIN / 4;
    vector<long long> dp(N + 1, NEG_INF);
    vector<long long> bestRow(MAXC + 1, NEG_INF), bestCol(MAXC + 1, NEG_INF);
    dp[1] = F[1];

    for (const auto &pr : order) {
        int u = pr.second;
        if (bestRow[Y[u]] != NEG_INF) {
            dp[u] = max(dp[u], bestRow[Y[u]] - K + F[u]);
        }
        if (bestCol[X[u]] != NEG_INF) {
            dp[u] = max(dp[u], bestCol[X[u]] - K + F[u]);
        }
        if (dp[u] >= K) {
            bestRow[Y[u]] = max(bestRow[Y[u]], dp[u]);
            bestCol[X[u]] = max(bestCol[X[u]], dp[u]);
        }
    }

    ensuref(dp[N] >= 0,
            "input guarantee says a path exists, but leaf N is unreachable");

    inf.readEof();
    return 0;
}
