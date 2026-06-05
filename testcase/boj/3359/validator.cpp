#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 999, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int a = inf.readInt(1, 998, "a_i");
        inf.readSpace();
        int b = inf.readInt(a + 1, 999, "b_i");
        inf.readEoln();
    }

    inf.readEof();
}
