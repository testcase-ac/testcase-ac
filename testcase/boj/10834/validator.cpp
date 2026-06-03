#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(1, 1000, "m");
    inf.readEoln();

    long long rpm = 1;
    for (int i = 1; i <= m; ++i) {
        long long a = inf.readLong(1LL, 1000000000LL, "a");
        inf.readSpace();
        long long b = inf.readLong(1LL, 1000000000LL, "b");
        inf.readSpace();
        inf.readInt(0, 1, "s");
        inf.readEoln();

        ensuref(gcd(a, b) == 1, "a and b must be coprime at belt %d: %lld %lld", i, a, b);
        ensuref(rpm % a == 0, "wheel %d rpm is not an integer", i + 1);

        __int128 next = (__int128)(rpm / a) * b;
        ensuref(1 <= next && next <= 1000000000LL,
                "wheel %d rpm is out of range", i + 1);
        rpm = (long long)next;
    }

    inf.readEof();
}
