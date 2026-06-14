#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 100, "p_i");
        inf.readSpace();
        inf.readInt(1, 3000, "c_i");
        inf.readEoln();
    }

    inf.readEof();
}
