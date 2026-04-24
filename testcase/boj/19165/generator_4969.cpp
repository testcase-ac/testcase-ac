#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small sizes for hand-checkability
    int N = rnd.next(1, 10);
    int Q = rnd.next(1, 20);

    // Hyper-parameter for initial A/B bias
    double pA = rnd.next();
    string S;
    S.reserve(N);
    for (int i = 0; i < N; i++) {
        S.push_back(rnd.next() < pA ? 'A' : 'B');
    }

    // Hyper-parameter for command type distribution
    double pType2 = 0.2 + rnd.next() * 0.6; // between 0.2 and 0.8

    vector<bool> isType2(Q);
    for (int i = 0; i < Q; i++) {
        isType2[i] = (rnd.next() < pType2);
    }
    // Ensure at least one type-2 command
    if (count(isType2.begin(), isType2.end(), true) == 0) {
        int idx = rnd.next(0, Q - 1);
        isType2[idx] = true;
    }

    // Output header
    println(N, Q);
    // Print S as a string
    printf("%s\n", S.c_str());

    int half = N / 2;
    int quarter = N / 4;

    for (int i = 0; i < Q; i++) {
        // Hyper-parameter for interval length diversity
        int L = rnd.next(1, N);
        int R;
        if (rnd.next() < 0.5) {
            // short interval
            int maxLen = max(0, quarter);
            int len = rnd.next(0, maxLen);
            R = min(N, L + len);
        } else {
            // long interval
            int minR = max(L, half);
            R = rnd.next(minR, N);
        }

        if (!isType2[i]) {
            // Type 1 command
            println(1, L, R);
        } else {
            // Type 2 command, small A, B for hand-checkability
            int maxAB = rnd.next(0, 20);
            int A = rnd.next(0, maxAB);
            int B = rnd.next(0, maxAB);
            println(2, L, R, A, B);
        }
    }

    return 0;
}
