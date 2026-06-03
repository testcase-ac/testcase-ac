#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 999, "T");
    inf.readEoln();

    for (int i = 0; i < t; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readInt(1, 9999, "N");
    }
    inf.readEoln();
    inf.readEof();
}
