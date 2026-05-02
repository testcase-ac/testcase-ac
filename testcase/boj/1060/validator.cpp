#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // L: size of set S
    int L = inf.readInt(1, 50, "L");
    inf.readEoln();

    vector<long long> S(L);
    for (int i = 0; i < L; ++i) {
        S[i] = inf.readLong(1LL, 1000000000LL, "S_i");
        if (i + 1 < L) inf.readSpace();
        else inf.readEoln();
    }

    // Check that all S elements are distinct
    {
        vector<long long> tmp = S;
        sort(tmp.begin(), tmp.end());
        for (int i = 1; i < L; ++i) {
            ensuref(tmp[i] != tmp[i-1],
                    "Elements of S must be distinct, but value %lld is duplicated",
                    tmp[i]);
        }
    }

    // n
    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    inf.readEof();
}
