#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 5000, "m");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int a = inf.readInt(0, m, "a_i");
        inf.readSpace();
        int b = inf.readInt(a, m, "b_i");
        inf.readEoln();
    }

    inf.readEof();
}
