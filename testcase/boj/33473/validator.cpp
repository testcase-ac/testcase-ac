#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // T: number of test cases
    long long T = inf.readLong(1LL, 1000000LL, "T");
    inf.readEoln();

    for (long long tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        // Read P and Q for this test case
        long long P = inf.readLong(1LL, 1000000000000000000LL, "P");
        inf.readSpace();
        long long Q = inf.readLong(1LL, 1000000000000000000LL, "Q");
        inf.readEoln();

        // P and Q are "서로소인 두 양의 정수" => gcd(P, Q) == 1
        long long g = std::gcd(P, Q);
        ensuref(g == 1, "P and Q must be coprime (gcd(P, Q) == 1), but gcd(%lld, %lld) = %lld (test case %lld)",
                P, Q, g, tc + 1);
    }

    inf.readEof();
}
