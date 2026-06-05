#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 20, "n");
    inf.readSpace();
    int k = inf.readInt(1, 22, "k");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int w = inf.readInt(1, 5, "w_i");
        inf.readSpace();
        int s = inf.readInt(1, 10, "s_i");
        inf.readSpace();
        int e = inf.readInt(s, 10, "e_i");
        inf.readEoln();

        (void)w;
        (void)e;
    }

    inf.readEof();
}
