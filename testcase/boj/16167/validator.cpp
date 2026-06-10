#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100, "N");
    inf.readSpace();
    int r = inf.readInt(1, 200, "R");
    inf.readEoln();

    for (int i = 1; i <= r; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readSpace();
        inf.readInt(1, 100, "c");
        inf.readSpace();
        inf.readInt(1, 100, "d");
        inf.readSpace();
        inf.readInt(1, 100, "e");
        inf.readEoln();

        // CHECK: The statement does not forbid loops or repeated directed routes.
        (void)a;
        (void)b;
    }

    inf.readEof();
}
