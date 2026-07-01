#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxN = 100000;
    const int maxSumN = 1000000;
    const long long maxValue = 1000000000LL;

    long long sumN = 0;
    int testCase = 0;

    while (!inf.eof()) {
        ++testCase;
        setTestCase(testCase);

        int n = inf.readInt(1, maxN, "n");
        inf.readSpace();
        inf.readLong(0LL, maxValue, "x");
        inf.readEoln();

        inf.readLongs(n, 0LL, maxValue, "a_i");
        inf.readEoln();

        inf.readLongs(n, 0LL, maxValue, "b_i");
        inf.readEoln();

        sumN += n;
        ensuref(sumN <= maxSumN, "sum of n exceeds %d: %lld", maxSumN, sumN);
    }

    ensuref(testCase > 0, "input must contain at least one test case");
    inf.readEof();
}
