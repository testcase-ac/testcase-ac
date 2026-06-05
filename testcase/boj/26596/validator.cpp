#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(1, 5000, "M");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        inf.readToken("[A-Za-z]{1,50}", "s_i");
        inf.readSpace();
        inf.readInt(1, 100, "x_i");
        inf.readEoln();
    }

    inf.readEof();
}
