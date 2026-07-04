#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr int MAX_T = 10000;
    constexpr long long MAX_N = 10000000LL;
    constexpr long long MAX_SUM_N = 20000000LL;
    constexpr long long MIN_A = -2000000000LL;
    constexpr long long MAX_A = 2000000000LL;
    constexpr long long MAX_U32 = 4294967295LL;

    int t = inf.readInt(1, MAX_T, "t");
    inf.readEoln();

    long long sumN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        long long n = inf.readLong(2LL, MAX_N, "n");
        inf.readSpace();
        long long l = inf.readLong(MIN_A, MAX_A, "l");
        inf.readSpace();
        long long r = inf.readLong(l, MAX_A, "r");
        inf.readSpace();

        // CHECK: The statement text is truncated after "b_1,b_2"; the generator
        // recurrence modulo 2^32 implies all recurrence parameters and seeds are uint32.
        inf.readLong(0LL, MAX_U32, "x");
        inf.readSpace();
        inf.readLong(0LL, MAX_U32, "y");
        inf.readSpace();
        inf.readLong(0LL, MAX_U32, "z");
        inf.readSpace();
        inf.readLong(0LL, MAX_U32, "b_1");
        inf.readSpace();
        inf.readLong(0LL, MAX_U32, "b_2");
        inf.readEoln();

        sumN += n;
        ensuref(sumN <= MAX_SUM_N, "sum of n exceeds %lld after test %d", MAX_SUM_N, tc);
    }

    inf.readEof();
}
