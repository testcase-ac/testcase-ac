#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int w = inf.readInt(1, 500, "W");
    inf.readSpace();
    int l = inf.readInt(1, 500, "L");
    inf.readEoln();

    for (int row = 1; row <= l; ++row) {
        for (int col = 1; col <= w; ++col) {
            if (col > 1) {
                inf.readSpace();
            }
            inf.readInt(0, 9999, "H");
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
