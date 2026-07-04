#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no upper bound for t. Limit total n to one
    // largest test case by local policy for unbounded multi-case inputs.
    constexpr int MAX_N = 100000;
    int t = inf.readInt(1, MAX_N, "t");
    inf.readEoln();

    long long sumN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        inf.readEoln();
        int n = inf.readInt(1, MAX_N, "n");
        inf.readEoln();

        sumN += n;
        ensuref(sumN <= MAX_N, "sum of n exceeds %d", MAX_N);
    }

    inf.readEof();
}
