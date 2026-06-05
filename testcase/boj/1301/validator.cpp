#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 5, "N");
    inf.readEoln();

    int total = 0;
    for (int i = 1; i <= n; ++i) {
        int count = inf.readInt(1, 10, "count");
        inf.readEoln();
        total += count;
    }

    ensuref(total <= 35, "sum of bead counts must be at most 35, got %d", total);

    inf.readEof();
}
