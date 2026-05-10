#include "testlib.h"

using namespace std;

long long altitude(int h, long long t) {
    // A = −6t^4 + h t^3 + 2t^2 + t
    long long t2 = t * t;
    long long t3 = t2 * t;
    long long t4 = t2 * t2;
    long long A = -6LL * t4 + 1LL * h * t3 + 2LL * t2 + t;
    return A;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Input is exactly two integers, each on its own line
    int h = inf.readInt(0, 100, "h");
    inf.readEoln();

    int M = inf.readInt(1, 239, "M");
    inf.readEoln();

    // Global property from statement:
    // "In order to do this, your program should use the formula to calculate
    //  the altitude when t = 1, t = 2, and so on, until the balloon touches
    //  the ground or t = M is reached."
    //
    // And in output description, it's guaranteed that either:
    // - balloon does not touch ground in given time, or
    // - there exists earliest hour T with A(T) <= 0.
    //
    // This is always mathematically true for given polynomial and bounds,
    // but we still simulate to be robust and to ensure no overflow issues
    // with intended ranges.

    bool touched = false;
    for (int t = 1; t <= M; ++t) {
        long long A = altitude(h, t);
        // No explicit bound on A in statement, but check no overflow
        // beyond int64 is needed: with t <= 239, all terms are well
        // within 64-bit range, so no extra ensuref needed here.
        if (A <= 0) {
            touched = true;
            break;
        }
    }
    // No need to enforce additional conditions; simulation just ensures
    // the formula evaluation stays within 64-bit, which it does for bounds.

    inf.readEof();
}
