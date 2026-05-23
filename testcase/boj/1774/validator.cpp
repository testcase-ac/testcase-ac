#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "M");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(0, 1000000, "X");
        inf.readSpace();
        inf.readInt(0, 1000000, "Y");
        inf.readEoln();
    }

    for (int i = 1; i <= m; ++i) {
        // CHECK: The statement gives existing paths but does not explicitly
        // forbid self-loops or duplicate paths, so only endpoint ranges are enforced.
        inf.readInt(1, n, "A");
        inf.readSpace();
        inf.readInt(1, n, "B");
        inf.readEoln();
    }

    inf.readEof();
}
