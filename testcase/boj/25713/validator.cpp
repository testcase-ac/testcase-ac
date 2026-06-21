#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "M");
    inf.readEoln();

    int k = inf.readInt(1, 2000, "K");
    inf.readEoln();

    for (int i = 1; i <= k; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, m, "b_i");
        inf.readSpace();
        int c = inf.readInt(a, n, "c_i");
        inf.readSpace();
        inf.readInt(b, m, "d_i");
        inf.readEoln();
    }

    inf.readEof();
}
