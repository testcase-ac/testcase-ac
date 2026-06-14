#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int a = inf.readInt(2, 1000000, "a_i");
        inf.readSpace();
        int b = inf.readInt(a, 1000000, "b_i");
        inf.readEoln();
    }

    inf.readEof();
}
