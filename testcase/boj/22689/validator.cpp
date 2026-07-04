#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long totalN = 0;
    int datasetCount = 0;

    while (true) {
        int n = inf.readInt(0, 1000, "N");
        inf.readSpace();
        int m = inf.readInt(0, 12, "M");
        inf.readEoln();

        if (n == 0 && m == 0) {
            break;
        }

        ++datasetCount;
        ensuref(n >= 1, "N must be positive before the terminating dataset");
        ensuref(m >= 1, "M must be positive before the terminating dataset");

        for (int j = 0; j < n; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            inf.readInt(0, m, "L_j");
        }
        inf.readEoln();

        totalN += n;
        // CHECK: the statement gives no dataset-count bound; this cap keeps
        // aggregate input size practical while allowing many small datasets.
        ensuref(datasetCount <= 100000, "too many datasets: %d", datasetCount);
        ensuref(totalN <= 1000000, "sum of N is too large: %lld", totalN);
    }

    inf.readEof();
}
