#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 200000;
    const long long MAXE = 1000000000LL;

    int N = inf.readInt(1, MAXN, "N");
    inf.readSpace();
    int Q = inf.readInt(1, MAXN, "Q");
    inf.readEoln();

    vector<long long> E(N + 1);
    for (int i = 1; i <= N; ++i) {
        E[i] = inf.readLong(1LL, MAXE, "E_i");
        if (i < N) inf.readSpace();
        else inf.readEoln();
    }

    vector<int> type(Q + 1);
    vector<int> d(Q + 1, -1), s(Q + 1, -1), e(Q + 1, -1);

    // For constraint: same d not multiple times
    vector<bool> usedD(N, false); // d in [1, N-1]

    for (int i = 1; i <= Q; ++i) {
        int t = inf.readInt(1, 2, "t");
        type[i] = t;
        if (t == 1) {
            inf.readSpace();
            int dd = inf.readInt(1, N - 1, "d");
            inf.readEoln();
            d[i] = dd;
            ensuref(!usedD[dd],
                    "d = %d used multiple times for type-1 operations (first index unknown, again at op %d)",
                    dd, i);
            usedD[dd] = true;
        } else {
            inf.readSpace();
            int ss = inf.readInt(1, N, "s");
            inf.readSpace();
            int ee = inf.readInt(1, N, "e");
            inf.readEoln();
            s[i] = ss;
            e[i] = ee;
            ensuref(ss <= ee, "For type-2 operation %d, s (%d) must be <= e (%d)", i, ss, ee);
        }
    }

    // Last operation must be type 2
    ensuref(type[Q] == 2, "Last operation must be of type 2");

    inf.readEof();
}
