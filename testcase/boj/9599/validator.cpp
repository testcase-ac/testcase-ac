#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int datasets = 0;
    while (true) {
        int n = inf.readInt(0, 20, "n");
        inf.readSpace();
        int k = inf.readInt(0, 10, "k");
        inf.readSpace();
        int s = inf.readInt(0, 155, "s");
        inf.readEoln();

        if (n == 0 && k == 0 && s == 0) {
            break;
        }

        ensuref(1 <= n, "n must be positive before the terminating line");
        ensuref(1 <= k, "k must be positive before the terminating line");
        ensuref(1 <= s, "s must be positive before the terminating line");

        ++datasets;
        ensuref(datasets <= 100, "number of datasets exceeds 100");
    }

    inf.readEof();
}
