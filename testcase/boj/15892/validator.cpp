#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 300, "n");
    inf.readSpace();
    int m = inf.readInt(1, 5000, "m");
    inf.readEoln();

    // CHECK: The statement gives m corridor objects and does not forbid multiple corridors between the same two rooms.
    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readSpace();
        inf.readInt(1, 100, "c");
        inf.readEoln();

        ensuref(a != b, "corridor %d has same endpoints: %d", i, a);
    }

    inf.readEof();
}
