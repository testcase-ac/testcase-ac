#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameter: size of permutation
    int N = rnd.next(1, 10);

    // Hyperparameter: permutation type
    // 0 = identity, 1 = single big cycle (if N>1), 2 = random shuffle
    int ptype = (N == 1 ? 0 : rnd.next(0, 2));

    vector<int> P(N);
    if (ptype == 0) {
        // identity
        for (int i = 0; i < N; i++) P[i] = i + 1;
    } else if (ptype == 1) {
        // one big cycle
        for (int i = 0; i < N - 1; i++) P[i] = i + 2;
        P[N - 1] = 1;
    } else {
        // random shuffle
        for (int i = 0; i < N; i++) P[i] = i + 1;
        shuffle(P.begin(), P.end());
    }

    // Hyperparameter: cost bound size
    int costBound = rnd.any(vector<int>{5, 20, 100});

    // Hyperparameter: cost correlation
    // 0 = independent, 1 = identical A=B, 2 = reversed B relative to bound
    int cmode = rnd.next(0, 2);

    vector<int> A(N), B(N);
    if (cmode == 0) {
        // independent costs
        for (int i = 0; i < N; i++) {
            A[i] = rnd.next(1, costBound);
            B[i] = rnd.next(1, costBound);
        }
    } else if (cmode == 1) {
        // identical costs
        for (int i = 0; i < N; i++) {
            A[i] = rnd.next(1, costBound);
            B[i] = A[i];
        }
    } else {
        // reversed B
        for (int i = 0; i < N; i++) {
            A[i] = rnd.next(1, costBound);
            B[i] = costBound + 1 - A[i];
            if (B[i] < 1) B[i] = 1;
        }
    }

    // Output
    println(N);
    println(P);
    println(A);
    println(B);

    return 0;
}
