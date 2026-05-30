#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

bool isSquareFree(long long d) {
    if (d <= 1) return true;
    for (long long p = 2; p * p <= d; ++p) {
        long long square = p * p;
        if (d % square == 0) return false;
    }
    return true;
}

long long absValue(long long x) {
    return x < 0 ? -x : x;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long LIM = 10;

    auto readComplex = [&](const char* name, array<long long, 8>& values) {
        for (int i = 0; i < 8; ++i) {
            values[i] = inf.readLong(-LIM, LIM, (string(name) + "_" + to_string(i)).c_str());
            if (i != 7) inf.readSpace();
        }
        inf.readEoln();

        long long a0 = values[0], b0 = values[1], c0 = values[2], d0 = values[3];
        long long a1 = values[4], b1 = values[5], c1 = values[6], d1 = values[7];

        ensuref(a0 > 0, "%s: a0 must be positive, got %lld", name, a0);
        ensuref(a1 > 0, "%s: a1 must be positive, got %lld", name, a1);

        ensuref(d0 >= 0 && d0 != 1, "%s: d0 must satisfy 0 <= d0 != 1, got %lld", name, d0);
        ensuref(d1 >= 0 && d1 != 1, "%s: d1 must satisfy 0 <= d1 != 1, got %lld", name, d1);
        ensuref(d0 == d1, "%s: d0 and d1 must be equal, got %lld and %lld", name, d0, d1);

        ensuref((c0 == 0) == (d0 == 0),
                "%s: c0 must be zero exactly when d0 is zero, got c0=%lld d0=%lld",
                name, c0, d0);
        ensuref((c1 == 0) == (d1 == 0),
                "%s: c1 must be zero exactly when d1 is zero, got c1=%lld d1=%lld",
                name, c1, d1);

        long long gcd0 = gcd(gcd(absValue(a0), absValue(b0)), absValue(c0));
        long long gcd1 = gcd(gcd(absValue(a1), absValue(b1)), absValue(c1));
        ensuref(gcd0 == 1, "%s: gcd(a0,b0,c0) must be 1, got %lld", name, gcd0);
        ensuref(gcd1 == 1, "%s: gcd(a1,b1,c1) must be 1, got %lld", name, gcd1);

        ensuref(d0 == 0 || isSquareFree(d0), "%s: d0 must be square-free, got %lld", name, d0);
        ensuref(d1 == 0 || isSquareFree(d1), "%s: d1 must be square-free, got %lld", name, d1);
    };

    array<long long, 8> A, B;
    readComplex("A", A);
    readComplex("B", B);

    ensuref(A[3] == B[3], "A and B must have the same d0, got %lld and %lld", A[3], B[3]);

    auto isZero = [](const array<long long, 8>& values) {
        return values[1] == 0 && values[2] == 0 && values[5] == 0 && values[6] == 0;
    };
    ensuref(!isZero(B), "B must be non-zero");

    inf.readEof();
}
