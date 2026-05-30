#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 100000;
    const int MAXM = 100000;
    const int MAXK = 100000; // per clause

    int n = inf.readInt(1, MAXN, "n");
    inf.readSpace();
    int m = inf.readInt(1, MAXM, "m");
    inf.readEoln();

    vector<int> cnt(n + 1, 0);

    for (int i = 0; i < m; ++i) {
        long long ki = inf.readLong(1LL, (long long)MAXK, "k_i");
        // sum of ki is not bounded in statement, so no global cap here
        // but ki individually must be within [1, 100000]
        // ki can be up to 1e5 but m up to 1e5; total literals may be large,
        // but that's per statement.
        for (long long j = 0; j < ki; ++j) {
            inf.readSpace();
            int lij = inf.readInt(-n, n, "l_ij");
            ensuref(lij != 0, "Literal value 0 is not allowed at clause %d position %lld", i + 1, j + 1);

            int var = abs(lij);
            cnt[var]++;
            ensuref(cnt[var] <= 2,
                    "Variable %d appears more than 2 times including negations (currently %d)",
                    var, cnt[var]);
        }
        inf.readEoln();
    }

    inf.readEof();
}
