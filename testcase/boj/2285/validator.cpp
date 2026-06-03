#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    long long total_population = 0;
    for (int i = 1; i <= n; ++i) {
        inf.readLong(-1000000000LL, 1000000000LL, "x_i");
        inf.readSpace();
        long long population = inf.readLong(0LL, 1000000000LL, "a_i");
        inf.readEoln();

        total_population += population;
    }

    ensuref(total_population > 0, "sum of all a_i must be positive");
    inf.readEof();
}
