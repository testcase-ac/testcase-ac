#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 7, "N");
    inf.readSpace();
    int a = inf.readInt(1, 150, "A");
    inf.readSpace();
    inf.readInt(a, 150, "B");
    inf.readEoln();

    for (int i = 1; i <= 10; ++i) {
        inf.readInt(1, 6, "X_i");
        inf.readSpace();
        inf.readInt(1, 6, "Y_i");
        inf.readEoln();
    }

    inf.readEof();
}
