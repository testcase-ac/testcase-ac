#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int Q_MIN = 1;
    const int Q_MAX = 1000000;
    const long long A_MIN = 1;
    const long long A_MAX = 1000000000LL;
    const long long B_MIN = 1;
    const long long B_MAX = 1000000000LL;
    const int D_MIN = 0;
    const int D_MAX = 100000;
    const long long SUM_D_MAX = 1000000LL;

    int Q = inf.readInt(Q_MIN, Q_MAX, "Q");
    inf.readEoln();

    long long sumD = 0;

    for (int i = 0; i < Q; ++i) {
        // a, b, d are integers in canonical decimal format
        long long a = inf.readLong(A_MIN, A_MAX, "a");
        inf.readSpace();
        long long b = inf.readLong(B_MIN, B_MAX, "b");
        inf.readSpace();
        int d = inf.readInt(D_MIN, D_MAX, "d");
        inf.readEoln();

        ensuref(a <= b, "Query %d: must satisfy a <= b, but got a = %lld, b = %lld", i + 1, a, b);

        sumD += d;
        ensuref(sumD <= SUM_D_MAX,
                "Sum of all d must be <= %lld, but exceeded after query %d (current sum = %lld)",
                SUM_D_MAX, i + 1, sumD);
    }

    inf.readEof();
}
