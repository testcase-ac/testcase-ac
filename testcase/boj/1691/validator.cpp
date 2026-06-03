#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int w = inf.readInt(1, 600, "W");
    inf.readSpace();
    int h = inf.readInt(1, 600, "H");
    inf.readEoln();

    int n = inf.readInt(1, 200, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        int wi = inf.readInt(1, w, "W_i");
        inf.readSpace();
        int hi = inf.readInt(1, h, "H_i");
        inf.readEoln();
        (void)wi;
        (void)hi;
    }

    inf.readEof();
}
