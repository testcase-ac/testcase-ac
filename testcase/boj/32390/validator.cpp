#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5000000, "N");
    inf.readSpace();
    int m = inf.readInt(1, n, "M");
    inf.readEoln();

    long long sum = 0;
    for (int i = 1; i <= m; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        int a = inf.readInt(1, n, "A_i");
        sum += a;
    }
    inf.readEoln();

    ensuref(sum == n, "sum of A_i must be N, got %lld instead of %d", sum, n);

    inf.readEof();
}
