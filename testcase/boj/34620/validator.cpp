#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// We will check that given reduced fraction a/b (1 <= a < b <= 1e9, gcd(a,b)=1)
// is representable by some 군꺾 문자열 and, if so, that the value is <= 10^9
// during the simulation, matching problem's guarantee "if representable then
// some string exists" (here we just validate input consistency and bounds).

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test case (problem does not mention multiple test cases).
    long long a = inf.readLong(1LL, 1000000000LL, "a");
    inf.readSpace();
    long long b = inf.readLong(1LL, 1000000000LL, "b");
    inf.readEoln();

    // Constraint: a < b
    ensuref(a < b, "Constraint violated: a (%lld) must be less than b (%lld).", a, b);

    // Constraint: gcd(a, b) = 1
    auto gcd_ll = [](long long x, long long y) {
        while (y) {
            long long t = x % y;
            x = y;
            y = t;
        }
        return x;
    };
    ensuref(gcd_ll(a, b) == 1, "Constraint violated: a (%lld) and b (%lld) must be coprime.", a, b);

    // No more input.
    inf.readEof();
}
