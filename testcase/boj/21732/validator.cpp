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

    // count appearances of each literal (variable or its negation)
    // index 1..n for positive, n+1..2n for negative
    vector<int> cnt(2 * n + 1, 0); // 1-based; index 0 unused

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
            int idx = (lij > 0 ? var : n + var);
            cnt[idx]++;
            ensuref(cnt[idx] <= 2,
                    "Variable %d with sign %c appears more than 2 times (currently %d)",
                    var, (lij > 0 ? '+' : '-'), cnt[idx]);
        }
        inf.readEoln();
    }

    inf.readEof();
}
