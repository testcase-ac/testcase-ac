#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int c = inf.readInt(1, 10000, "C");
    inf.readSpace();
    int n = inf.readInt(1, 10000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 10000, "M");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 10000, "s_i");
        inf.readSpace();
        inf.readInt(1, 10000, "p_i");
        inf.readEoln();
    }

    inf.readEof();
}
