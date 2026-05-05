#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

bool isSquareFree(long long d) {
    if (d <= 1) return true; // for d=0 or 1 this condition is not required
    for (long long p = 2; p * p <= d; ++p) {
        long long sq = p * p;
        if (d % sq == 0) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long LIM = 10;

    auto readComplex = [&](const char* who,
                           array<long long,8> &v) {
        // read 8 integers: a0,b0,c0,d0,a1,b1,c1,d1
        for (int i = 0; i < 8; ++i) {
            v[i] = inf.readLong(-LIM, LIM, (string(who) + "_" + to_string(i)).c_str());
            if (i != 7) inf.readSpace();
        }
        inf.readEoln();

        long long a0 = v[0], b0 = v[1], c0 = v[2], d0 = v[3];
        long long a1 = v[4], b1 = v[5], c1 = v[6], d1 = v[7];

        // a_j > 0
        ensuref(a0 > 0 && a1 > 0,
                "%s: a_j must be > 0 (a0=%lld, a1=%lld)", who, a0, a1);

        // 0 <= d_j != 1  (and |d_j|<=10 from reading)
        ensuref(0 <= d0 && d0 != 1, "%s: d0 must satisfy 0 <= d0 != 1 (d0=%lld)", who, d0);
        ensuref(0 <= d1 && d1 != 1, "%s: d1 must satisfy 0 <= d1 != 1 (d1=%lld)", who, d1);

        // 'c_j = 0' and 'd_j = 0' are necessary and sufficient conditions
        // so (c_j == 0) <=> (d_j == 0)
        ensuref((c0 == 0) == (d0 == 0),
                "%s: (c0 == 0) must be equivalent to (d0 == 0) (c0=%lld, d0=%lld)",
                who, c0, d0);
        ensuref((c1 == 0) == (d1 == 0),
                "%s: (c1 == 0) must be equivalent to (d1 == 0) (c1=%lld, d1=%lld)",
                who, c1, d1);

        // gcd(a_j, b_j, c_j) = 1
        auto gg = [](long long x){ return x >= 0 ? x : -x; };
        long long g0 = std::gcd(std::gcd(gg(a0), gg(b0)), gg(c0));
        long long g1 = std::gcd(std::gcd(gg(a1), gg(b1)), gg(c1));
        ensuref(g0 == 1,
                "%s: gcd(a0,b0,c0) must be 1 (a0=%lld,b0=%lld,c0=%lld,gcd=%lld)",
                who, a0, b0, c0, g0);
        ensuref(g1 == 1,
                "%s: gcd(a1,b1,c1) must be 1 (a1=%lld,b1=%lld,c1=%lld,gcd=%lld)",
                who, a1, b1, c1, g1);

        // when d_j > 0, d_j has no square divisor > 1  (square-free)
        if (d0 > 0) {
            ensuref(isSquareFree(d0),
                    "%s: d0 must be square-free when >0 (d0=%lld)", who, d0);
        }
        if (d1 > 0) {
            ensuref(isSquareFree(d1),
                    "%s: d1 must be square-free when >0 (d1=%lld)", who, d1);
        }
    };

    array<long long,8> A, B;
    readComplex("A", A);
    readComplex("B", B);

    long long Ad0 = A[3];
    long long Ad1 = A[7];
    long long Bd0 = B[3];
    long long Bd1 = B[7];

    // A and B must have same d0
    ensuref(Ad0 == Bd0,
            "A and B must have the same d0 (A.d0=%lld, B.d0=%lld)", Ad0, Bd0);

    // Problem statement: A and B’s d0 values are identical (already checked),
    // and B != 0.
    // Represent:
    // A = (b0 + c0*sqrt(d0))/a0 + (b1 + c1*sqrt(d1))/a1 * i
    auto isZero = [](const array<long long,8> &v) {
        long long a0 = v[0], b0 = v[1], c0 = v[2];
        long long a1 = v[4], b1 = v[5], c1 = v[6];
        // real part zero: b0 + c0*sqrt(d0) == 0  and
        // imag part zero: b1 + c1*sqrt(d1) == 0.
        // Since both 1 and sqrt(d) are linearly independent over Q,
        // this implies b_j==0 and c_j==0.
        return (b0 == 0 && c0 == 0 && b1 == 0 && c1 == 0);
    };
    ensuref(!isZero(B),
            "B must be non-zero");

    inf.readEof();
}
