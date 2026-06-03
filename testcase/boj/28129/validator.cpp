#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 3000, "N");
    inf.readSpace();
    inf.readInt(0, 3000, "K");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int a = inf.readInt(1, 3000, "a_i");
        inf.readSpace();
        int b = inf.readInt(a, 3000, "b_i");
        inf.readEoln();
    }

    inf.readEof();
}
