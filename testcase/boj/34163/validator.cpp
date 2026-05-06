#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 100000;
    const int MAX_K = 1000000;
    const int MAX_A = 1000000000;

    int N = inf.readInt(1, MAX_N, "N");
    inf.readSpace();
    int K = inf.readInt(5, MAX_K, "K");
    inf.readEoln();

    vector<long long> A(N);
    for (int i = 0; i < N; ++i) {
        A[i] = inf.readLong(1LL, (long long)MAX_A, "A_i");
        if (i + 1 < N) inf.readSpace();
    }
    inf.readEoln();

    for (int i = 0; i < N; ++i) {
        long long x = A[i];
        bool ok = false;
        if (x == 1 || x == 3 || x == 4) ok = true;
        if (!ok) {
            if (x % K == 0) {
                long long m = x / K;
                if (m > 0 && x <= MAX_A) ok = true;
            }
        }
        ensuref(ok, "A[%d] = %lld is invalid: must be 1,3,4 or positive multiple of K <= 1e9",
                i + 1, x);
    }

    inf.readEof();
}
