#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int s = inf.readInt(1, 200, "s_i");
        inf.readSpace();
        int e = inf.readInt(s, 200, "e_i");
        inf.readEoln();
    }

    inf.readEof();
}
