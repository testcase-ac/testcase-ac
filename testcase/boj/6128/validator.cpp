#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Check whether there exists at least one ordered 4-tuple (a,b,c,d)
// of non-negative integers such that a^2 + b^2 + c^2 + d^2 = N.
static bool hasRepresentation(int N) {
    // Simple brute-force with pruning; N <= 10000
    int limit = (int)floor(sqrt((double)N));
    for (int a = 0; a <= limit; ++a) {
        int remA = N - a * a;
        if (remA < 0) break;
        int limitB = (int)floor(sqrt((double)remA));
        for (int b = 0; b <= limitB; ++b) {
            int remB = remA - b * b;
            if (remB < 0) break;
            int limitC = (int)floor(sqrt((double)remB));
            for (int c = 0; c <= limitC; ++c) {
                int remC = remB - c * c;
                if (remC < 0) break;
                int d2 = remC;
                int d = (int)floor(sqrt((double)d2));
                if (d * d == d2) {
                    // Found non-negative integers a,b,c,d
                    return true;
                }
            }
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single integer N, with canonical integer formatting.
    int N = inf.readInt(1, 10000, "N");
    inf.readEoln();

    // Problem implicitly guarantees that at least one way exists
    // (since answer is defined as number of ways). Enforce that by checking.
    ensuref(hasRepresentation(N),
            "Given N=%d has no representation as sum of four squares of non-negative integers.",
            N);

    inf.readEof();
}
