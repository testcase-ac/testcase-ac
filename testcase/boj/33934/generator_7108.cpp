#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int type = -1;
    if (argc >= 2) type = atoi(argv[1]);
    if (type < 0 || type > 8) type = rnd.next(0, 8);

    int N = 0, S = 1, E = 2;
    vector<int> A;
    long long K = 2;

    auto pickRandomSE = [&](int n) {
        S = rnd.next(1, n);
        do { E = rnd.next(1, n); } while (E == S);
    };

    if (type == 0) {
        // General small random
        N = rnd.next(2, 12);
        A.resize(N);
        for (int i = 0; i < N; ++i) A[i] = rnd.next(1, 9);
        pickRandomSE(N);
        long long TOT = 0; for (int x : A) TOT += x;
        int mode = rnd.next(0, 3);
        if (mode == 0) K = rnd.next(2LL, TOT);
        else if (mode == 1) K = TOT;
        else if (mode == 2) K = min(1000000000LL, TOT + (long long)rnd.next(1, 5));
        else K = 1000000000LL;
    } else if (type == 1) {
        // Many ones (bottlenecks)
        N = rnd.next(3, 12);
        A.resize(N);
        for (int i = 0; i < N; ++i) A[i] = (rnd.next(0, 99) < 60 ? 1 : rnd.next(2, 6));
        pickRandomSE(N);
        long long TOT = 0; for (int x : A) TOT += x;
        int mode = rnd.next(0, 2);
        if (mode == 0) K = rnd.next(2LL, TOT);
        else if (mode == 1) K = TOT;
        else K = min(1000000000LL, TOT + (long long)rnd.next(1, 3));
    } else if (type == 2) {
        // Two or three lakes, edgey K choices
        N = rnd.next(2, 3);
        A.resize(N);
        for (int i = 0; i < N; ++i) A[i] = rnd.next(1, 9);
        pickRandomSE(N);
        long long TOT = 0; for (int x : A) TOT += x;
        vector<long long> cand;
        cand.push_back(2);
        cand.push_back(3);
        cand.push_back(TOT);
        cand.push_back(max(2LL, TOT - 1));
        K = rnd.any(cand);
    } else if (type == 3) {
        // S at 1, E at N
        N = rnd.next(4, 12);
        A.resize(N);
        for (int i = 0; i < N; ++i) A[i] = rnd.next(1, 8);
        S = 1; E = N;
        long long TOT = 0; for (int x : A) TOT += x;
        int mode = rnd.next(0, 3);
        if (mode == 0) K = rnd.next(2LL, TOT);
        else if (mode == 1) K = TOT;
        else K = min(1000000000LL, TOT + (long long)rnd.next(1, 4));
    } else if (type == 4) {
        // K = 2, adjacent lakes required
        N = rnd.next(2, 10);
        A.resize(N);
        for (int i = 0; i < N; ++i) A[i] = rnd.next(1, 9);
        if (N == 2) { S = rnd.next(1, 2); E = 3 - S; }
        else {
            S = rnd.next(1, N);
            if (S == 1) E = 2;
            else if (S == N) E = N - 1;
            else E = S + (rnd.next(0, 1) ? 1 : -1);
        }
        K = 2;
    } else if (type == 5) {
        // K = total stones
        N = rnd.next(2, 10);
        A.resize(N);
        for (int i = 0; i < N; ++i) A[i] = rnd.next(1, 7);
        pickRandomSE(N);
        long long TOT = 0; for (int x : A) TOT += x;
        K = TOT;
    } else if (type == 6) {
        // K = total stones + 1 (should be impossible)
        N = rnd.next(2, 10);
        A.resize(N);
        for (int i = 0; i < N; ++i) A[i] = rnd.next(1, 6);
        pickRandomSE(N);
        long long TOT = 0; for (int x : A) TOT += x;
        K = min(1000000000LL, TOT + 1);
    } else if (type == 7) {
        // Huge K (1e9)
        N = rnd.next(2, 12);
        A.resize(N);
        for (int i = 0; i < N; ++i) A[i] = rnd.next(1, 10);
        pickRandomSE(N);
        K = 1000000000LL;
    } else if (type == 8) {
        // One large lake among small ones
        N = rnd.next(3, 10);
        A.assign(N, 0);
        int big = rnd.next(1, N);
        for (int i = 1; i <= N; ++i) {
            if (i == big) A[i - 1] = rnd.next(15, 40);
            else A[i - 1] = rnd.next(1, 5);
        }
        // Make S/E sometimes target big lake
        int mode = rnd.next(0, 2);
        if (mode == 0) { S = big; do { E = rnd.next(1, N); } while (E == S); }
        else if (mode == 1) { E = big; do { S = rnd.next(1, N); } while (E == S); }
        else pickRandomSE(N);
        long long TOT = 0; for (int x : A) TOT += x;
        vector<long long> cand;
        cand.push_back(2);
        cand.push_back(max(2LL, TOT - 1));
        cand.push_back(TOT);
        cand.push_back(min(1000000000LL, TOT + (long long)rnd.next(1, 5)));
        K = rnd.any(cand);
    }

    // Final safety: ensure constraints and compactness
    // N in [2, 200000], Ai in [1,1000], K in [2,1e9] already ensured by design.

    println(N, S, E);
    println(A);
    println(K);

    return 0;
}
