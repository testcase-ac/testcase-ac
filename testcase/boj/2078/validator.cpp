#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Check that starting from (1,1) we can reach (A,B) using the given tree rules,
// and that the path is unique and well-defined going backwards.
void checkReachable(long long A, long long B) {
    // Problem guarantees "잘못된 입력은 주어지지 않는다", but we still verify.
    // Reverse process: from (A,B) go back to (1,1) by subtracting the smaller
    // from the larger while both > 0, mimicking the Euclidean algorithm.
    long long a = A, b = B;
    long long steps = 0;
    const long long LIMIT = 5'000'000'000LL; // just a generous upper safety

    while (!(a == 1 && b == 1)) {
        ensuref(a > 0 && b > 0, "Pair (%lld, %lld) is not reachable: non-positive encountered (%lld, %lld)",
                A, B, a, b);

        if (a == b) {
            // From the construction, except at (1,1), coordinates are never equal.
            ensuref(false, "Pair (%lld, %lld) is not reachable: equal coordinates (%lld, %lld) before reaching (1,1)",
                    A, B, a, b);
        }

        if (a > b) {
            long long k = (a - 1) / b; // number of left moves in compressed form
            ensuref(k >= 1, "Internal error: k < 1 when a > b");
            a -= k * b;
        } else {
            long long k = (b - 1) / a; // number of right moves in compressed form
            ensuref(k >= 1, "Internal error: k < 1 when b > a");
            b -= k * a;
        }

        steps++;
        ensuref(steps <= LIMIT, "Too many steps while checking reachability for (%lld, %lld)", A, B);
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test case: two integers A, B
    long long A = inf.readLong(1LL, 2000000000LL, "A");
    inf.readSpace();
    long long B = inf.readLong(1LL, 2000000000LL, "B");
    inf.readEoln();

    // Global property: the problem states that invalid input will not be given,
    // which implies (A,B) must correspond to some node in the infinite tree.
    // We verify this by reverse-simulating to (1,1).
    checkReachable(A, B);

    inf.readEof();
}
