#include "testlib.h"
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test case (problem statement doesn't mention multiple)
    long long W = inf.readLong(1LL, 1000000000LL, "W");
    inf.readSpace();
    long long H = inf.readLong(1LL, 1000000000LL, "H");
    inf.readSpace();
    long long f = inf.readLong(0LL, W, "f");
    inf.readSpace();
    long long c = inf.readLong(0LL, 1000LL, "c");
    inf.readSpace();
    long long x1 = inf.readLong(0LL, 1000000000LL, "x1"); // upper bounds refined below
    inf.readSpace();
    long long y1 = inf.readLong(0LL, 1000000000LL, "y1");
    inf.readSpace();
    long long x2 = inf.readLong(0LL, 1000000000LL, "x2");
    inf.readSpace();
    long long y2 = inf.readLong(0LL, 1000000000LL, "y2");
    inf.readEoln();

    // Check divisibility: c+1 is a divisor of H
    long long blocks = c + 1;
    ensuref(blocks > 0, "c+1 must be positive");
    ensuref(H % blocks == 0, "H must be divisible by c+1, but H=%lld, c+1=%lld", H, blocks);
    long long blockH = H / blocks;

    // Now check the remaining constraints from statement
    long long maxX = max(f, W - f);
    ensuref(0LL <= x1 && x1 < x2 && x2 <= maxX,
            "x1, x2 must satisfy 0 <= x1 < x2 <= max(f, W-f). Got x1=%lld, x2=%lld, f=%lld, W=%lld",
            x1, x2, f, W);

    ensuref(0LL <= y1 && y1 < y2 && y2 <= blockH,
            "y1, y2 must satisfy 0 <= y1 < y2 <= H/(c+1). Got y1=%lld, y2=%lld, H=%lld, c=%lld",
            y1, y2, H, c);

    // Also implicitly ensure the painted rectangle is non-empty
    ensuref(x2 - x1 > 0 && y2 - y1 > 0,
            "Painted rectangle must have positive area, but got width=%lld, height=%lld",
            x2 - x1, y2 - y1);

    // No further global guarantees (like answer existence bound) are stated that
    // need simulation; the problem only assumes valid ranges and divisibility.

    inf.readEof();
}
