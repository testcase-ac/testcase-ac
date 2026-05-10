#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

bool canConnect(const string& S, const string& T) {
    int n = (int)S.size();
    int m = (int)T.size();
    int maxk = min(n, m);
    for (int k = 1; k <= maxk; ++k) {
        bool ok1 = true;
        for (int i = 0; i < k; ++i) {
            if (S[i] != T[m - k + i]) { ok1 = false; break; }
        }
        if (ok1) return true;

        bool ok2 = true;
        for (int i = 0; i < k; ++i) {
            if (S[n - k + i] != T[i]) { ok2 = false; break; }
        }
        if (ok2) return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    vector<string> names;
    names.reserve(N);

    for (int i = 0; i < N; ++i) {
        string s = inf.readToken("[a-z]{1,20}", "name");
        inf.readEoln();
        names.push_back(s);
    }

    // Compute the number of connectable unordered pairs to validate that
    // the answer fits in a typical 64-bit signed integer (as implied by output).
    // Max pairs is C(100,2)=4950, so it is trivially safe, but we still ensure logic.
    long long cnt = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if (canConnect(names[i], names[j]) || canConnect(names[j], names[i])) {
                ++cnt;
            }
        }
    }
    // cnt is small; no further constraint given, so no additional ensuref needed here.

    inf.readEof();
}
