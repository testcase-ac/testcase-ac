#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 20, "T");
    inf.readEoln();

    long long sumK = 0;
    for (int i = 1; i <= t; ++i) {
        setTestCase(i);
        int k = inf.readInt(1, 4000000, "k");
        inf.readEoln();
        sumK += k;
    }

    ensuref(sumK <= 4000000, "sum of k must not exceed 4000000, got %lld", sumK);
    inf.readEof();
}
