#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int T_MAX = 100000;
    int lineCount = 0;

    // The problem describes: each line contains n and k, with ranges:
    // 0 ≤ n ≤ 1e9, 1 ≤ k ≤ 1e9.
    // There is no explicit test case count; input ends at EOF.
    // We must be whitespace-strict and ensure canonical integer format,
    // which readInt already enforces.

    while (!inf.seekEof()) {
        // Limit number of lines (test cases)
        ensuref(lineCount < T_MAX, "Too many lines: more than %d", T_MAX);
        ++lineCount;

        long long n = inf.readLong(0LL, 1000000000LL, "n");
        inf.readSpace();
        long long k = inf.readLong(1LL, 1000000000LL, "k");
        inf.readEoln();

        // No additional global properties are imposed by the statement,
        // so nothing more to validate per line.
        (void)n;
        (void)k;
    }

    inf.readEof();
}
