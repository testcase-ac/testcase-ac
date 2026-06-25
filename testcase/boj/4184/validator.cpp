#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(1, 1000, "r");
    inf.readSpace();
    int c = inf.readInt(1, 1000, "c");
    inf.readEoln();

    for (int i = 0; i < r; ++i) {
        inf.readToken("[0-7]{" + std::to_string(c) + "}", "grid_row");
        inf.readEoln();
    }

    // CHECK: The statement only gives an upper bound for n, so zero trips are valid.
    int n = inf.readInt(0, 50, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(1, r, "rs");
        inf.readSpace();
        inf.readInt(1, c, "cs");
        inf.readSpace();
        inf.readInt(1, r, "rd");
        inf.readSpace();
        inf.readInt(1, c, "cd");
        inf.readEoln();
    }

    inf.readEof();
}
