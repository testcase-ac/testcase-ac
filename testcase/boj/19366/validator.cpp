#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long MIN_N = 1LL;
    const long long MAX_N = 1000000000LL;
    const int MAX_T = 20000;

    int testCount = 0;

    // The problem has zero or more test cases until EOF.
    // Each test case is a single integer n on its own line.
    while (!inf.seekEof()) {
        // Read n with canonical integer form and range check.
        long long n = inf.readLong(MIN_N, MAX_N, "n");
        testCount++;

        ensuref(testCount <= MAX_T,
                "Number of test cases exceeds the limit: %d (max %d)",
                testCount, MAX_T);

        // Each test case line must end with exactly one newline.
        inf.readEoln();
    }

    // Entire file must end exactly at EOF (already implied by loop condition).
    inf.readEof();
}
