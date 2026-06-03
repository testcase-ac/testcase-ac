#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readToken("[a-z]{1,2000}", "S");
    inf.readEoln();

    int n = inf.readInt(1, 2000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readToken("[a-z]{1,2000}", "T_i");
        inf.readEoln();
    }

    inf.readEof();
}
