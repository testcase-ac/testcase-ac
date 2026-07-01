#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int queryCount = 0;
    while (true) {
        int n = inf.readInt(-1, 16, "n");
        inf.readEoln();

        if (n == -1) {
            break;
        }

        ensuref(n >= 2, "n must be in the range [2, 16], found %d", n);
        ++queryCount;
        // CHECK: The statement gives no number of query lines, so cap it at
        // 100000 to keep validation and stress inputs practical.
        ensuref(queryCount <= 100000, "too many query lines: %d", queryCount);
    }

    inf.readEof();
}
