#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int v = inf.readInt(1, 1000000, "V");
    (void)v;
    inf.readSpace();
    int r = inf.readInt(1, 100, "R");
    inf.readSpace();
    int c = inf.readInt(1, 100, "C");
    inf.readEoln();

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            inf.readInt(-25, 25, "height");
        }
        inf.readEoln();
    }

    inf.readEof();
}
