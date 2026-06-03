#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int a = inf.readInt(1, 99, "A_i");
        inf.readSpace();
        int b = inf.readInt(a + 1, 100, "B_i");
        inf.readSpace();
        inf.readInt(1, 100, "C_i");
        inf.readSpace();
        inf.readInt(1, 100, "D_i");
        inf.readEoln();
    }

    inf.readEof();
}
