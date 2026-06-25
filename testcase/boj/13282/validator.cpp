#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int datasets = 0;
    while (true) {
        int m = inf.readInt(0, 100, "m");
        inf.readSpace();
        int n = inf.readInt(0, 500000, "n");
        inf.readEoln();

        if (m == 0 && n == 0) {
            break;
        }

        ++datasets;
        setTestCase(datasets);
        ensuref(datasets <= 50, "too many datasets: %d", datasets);
        ensuref(2 <= m, "dataset %d has m below 2: %d", datasets, m);
        ensuref(1 <= n, "dataset %d has n below 1: %d", datasets, n);
    }

    inf.readEof();
}
