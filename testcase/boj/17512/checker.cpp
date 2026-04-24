#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int n;
vector<string> mat;

// Read and validate one answer (either jury's or participant's).
// On error, quits with _fail if stream==ans, or _wa if stream==ouf.
vector<int> readAns(InStream &stream) {
    // Compute required chain length K = 1 + floor(log2(n))
    int K = 1;
    while ((1 << K) <= n) ++K;

    vector<int> chain(K);
    for (int i = 0; i < K; i++) {
        char buf[30];
        sprintf(buf, "chain[%d]", i + 1);
        chain[i] = stream.readInt(1, n, buf);
    }
    // Check all distinct
    vector<bool> used(n + 1, false);
    for (int i = 0; i < K; i++) {
        int v = chain[i];
        if (used[v]) {
            stream.quitf(_wa, "student %d appears more than once in the chain", v);
        }
        used[v] = true;
    }
    // Check ordering: for all i<j, chain[i] beats chain[j]
    for (int i = 0; i < K; i++) {
        for (int j = i + 1; j < K; j++) {
            int u = chain[i], v = chain[j];
            if (mat[u-1][v-1] != 'W') {
                stream.quitf(_wa, "student %d does not beat student %d", u, v);
            }
        }
    }
    return chain;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int T = inf.readInt();
    for (int tc = 0; tc < T; tc++) {
        n = inf.readInt();
        mat.resize(n);
        for (int i = 0; i < n; i++) {
            mat[i] = inf.readToken();
            if ((int)mat[i].size() != n) {
                // Input format guarantee, but just in case
                inf.quitf(_fail, "bad input format at test %d, line %d", tc+1, i+1);
            }
        }
        // First verify jury's answer is valid (abort with _fail on its error)
        readAns(ans);
        // Then verify participant's answer (abort with _wa on error)
        readAns(ouf);
    }
    quitf(_ok, "All chains are valid");
    return 0;
}
