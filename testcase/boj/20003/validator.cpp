#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(1, 40, "A");
        inf.readSpace();
        inf.readInt(1, 40, "B");
        inf.readEoln();
    }

    inf.readEof();
}
