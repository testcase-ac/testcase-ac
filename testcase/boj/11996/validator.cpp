#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 1000, "n");
    inf.readEoln();

    long long totalCows = 0;
    for (int i = 1; i <= n; ++i) {
        int cows = inf.readInt(0, n, "c_i");
        inf.readEoln();
        totalCows += cows;
    }

    ensuref(totalCows == n, "sum of c_i must be n, found %lld for n=%d", totalCows, n);

    inf.readEof();
}
