#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long kIntMin = -(1LL << 31);
    const long long kIntMax = (1LL << 31) - 1;

    inf.readLong(kIntMin, kIntMax, "range_endpoint_1");
    inf.readSpace();
    inf.readLong(kIntMin, kIntMax, "range_endpoint_2");
    inf.readEoln();

    long long x = inf.readLong(kIntMin, kIntMax, "x");
    inf.readSpace();
    long long y = inf.readLong(kIntMin, kIntMax, "y");
    inf.readEoln();

    ensuref(x != 0, "x must be nonzero because the remainder is modulo |x|");

    long long absX = x < 0 ? -x : x;
    ensuref(0 <= y && y < absX,
            "remainder y must satisfy 0 <= y < |x|, got x=%lld y=%lld",
            x, y);

    inf.readEof();
}
