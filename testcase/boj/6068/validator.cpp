#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 1000, "t_i");
        inf.readSpace();
        inf.readInt(1, 1000000, "s_i");
        inf.readEoln();
    }

    inf.readEof();
}
