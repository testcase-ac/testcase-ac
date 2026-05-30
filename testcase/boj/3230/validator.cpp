#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 100, "N");
    inf.readSpace();
    int m = inf.readInt(3, n, "M");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, i, "first_run_position");
        inf.readEoln();
    }

    for (int i = 1; i <= m; ++i) {
        inf.readInt(1, i, "second_run_position");
        inf.readEoln();
    }

    inf.readEof();
}
