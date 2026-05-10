#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

static long long gcd_ll(long long a, long long b) {
    while (b != 0) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

// Check if there exists natural numbers x,y >= 1 s.t.
// gcd(x,y) = a and x + y = b, with given a,b (1 <= a,b <= 1e18).
// We validate the statement guarantee by verifying whether the answer
// is indeed 0 or 1 and consistent with the mathematical condition:
// Let x = a*u, y = a*v, gcd(u,v)=1, u+v = b/a. So:
// 1) b is divisible by a, let s = b/a;
// 2) s >= 2 (since u,v >=1);
// 3) There exist coprime positive integers u,v with u+v = s,
//    which is equivalent to gcd(s,1) = 1 always being possible
//    because we can take (1, s-1) and gcd(1, s-1)=1.
// So existence iff (b % a == 0) and (b / a >= 2).
static bool exists_pair(long long a, long long b) {
    if (b % a != 0) return false;
    long long s = b / a;
    return s >= 2;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long MIN_AB = 1LL;
    const long long MAX_AB = 1000000000000000000LL; // 1e18

    int Q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    for (int i = 0; i < Q; ++i) {
        long long a = inf.readLong(MIN_AB, MAX_AB, "a");
        inf.readSpace();
        long long b = inf.readLong(MIN_AB, MAX_AB, "b");
        inf.readEoln();

        // No further input-format constraints besides ranges and canonical
        // form are given. However, statement guarantees that we only need to
        // answer existence; there is no extra promise about always existing,
        // bounds on answer, or similar that must be enforced.
        //
        // We *could* compute exists_pair(a,b) here, but the problem statement
        // does not assert any additional global condition like "answer
        // always exists" or "answer is at most X", so from the validator's
        // perspective we do not enforce anything about the result.
        //
        // Still, if we wanted to sanity-check internal consistency or to
        // guard against accidental overflow in generators, we can at least
        // assert our math is well-defined (no overflow occurs in b/a etc.),
        // which is trivially true given bounds and types.
        (void)exists_pair; // to avoid unused function warning if not used
    }

    inf.readEof();
}
