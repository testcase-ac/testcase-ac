#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int datasetCount = 0;
    while (true) {
        long long a = inf.readLong(0LL, 1000000000LL, "A");
        inf.readSpace();
        long long b = inf.readLong(0LL, 1000099999LL, "B");
        inf.readSpace();
        long long p = inf.readLong(0LL, 1000000000LL, "P");
        inf.readEoln();

        if (a == 0 && b == 0 && p == 0) {
            break;
        }

        ensuref(a >= 1, "A must be positive in dataset %d", datasetCount + 1);
        ensuref(p >= 1, "P must be positive in dataset %d", datasetCount + 1);
        ensuref(a <= b, "A must not exceed B in dataset %d", datasetCount + 1);
        ensuref(b - a < 100000,
                "B - A must be less than 100000 in dataset %d", datasetCount + 1);

        ++datasetCount;
    }

    inf.readEof();
    return 0;
}
