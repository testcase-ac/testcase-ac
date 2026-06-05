#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int k = inf.readInt(0, 10000, "K");
    inf.readEoln();

    int n = inf.readInt(2, 100, "N");
    inf.readEoln();

    int r = inf.readInt(1, 10000, "R");
    inf.readEoln();

    for (int i = 1; i <= r; ++i) {
        int s = inf.readInt(1, n, "s");
        inf.readSpace();
        int d = inf.readInt(1, n, "d");
        inf.readSpace();
        int l = inf.readInt(1, 100, "l");
        inf.readSpace();
        int t = inf.readInt(0, 100, "t");
        inf.readEoln();

        (void)s;
        (void)d;
        (void)l;
        (void)t;
    }

    (void)k;
    inf.readEof();
}
