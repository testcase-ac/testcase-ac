#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 10000, "m");
    inf.readSpace();
    int x = inf.readInt(1, n, "x");
    inf.readSpace();
    inf.readInt(1, 1000, "y");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();

        // CHECK: The bounds allow n=1, but each edge is stated to connect two different vertices.
        ensuref(a != b, "edge %d is a loop at vertex %d", i, a);
    }

    inf.readEof();
}
