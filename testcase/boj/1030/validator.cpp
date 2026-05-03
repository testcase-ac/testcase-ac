#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

long long ipow(long long a, int e) {
    long long res = 1;
    while (e--) res *= a;
    return res;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // S ∈ [0,10], N ∈ [3,8], K ∈ [1, N-2]
    int S = inf.readInt(0, 10, "S");
    inf.readSpace();

    int N = inf.readInt(3, 8, "N");
    inf.readSpace();

    int K = inf.readInt(1, N - 2, "K");
    inf.readSpace();

    // (N - K) must be even
    ensuref((N - K) % 2 == 0, "(N - K) mod 2 must be 0");

    long long limit = ipow(N, S) - 1;

    // Coordinates ∈ [0, N^S - 1]
    long long R1 = inf.readLong(0, limit, "R1");
    inf.readSpace();

    long long R2 = inf.readLong(0, limit, "R2");
    inf.readSpace();

    long long C1 = inf.readLong(0, limit, "C1");
    inf.readSpace();

    long long C2 = inf.readLong(0, limit, "C2");
    inf.readEoln();

    // Window size ≤ 50
    ensuref(R1 <= R2, "R1 <= R2");
    ensuref(R2 <= R1 + 49, "R2 - R1 <= 49");

    ensuref(C1 <= C2, "C1 <= C2");
    ensuref(C2 <= C1 + 49, "C2 - C1 <= 49");

    inf.readEof();
    return 0;
}