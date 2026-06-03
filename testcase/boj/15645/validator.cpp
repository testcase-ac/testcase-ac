#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(0, 9, "a");
        inf.readSpace();
        inf.readInt(0, 9, "b");
        inf.readSpace();
        inf.readInt(0, 9, "c");
        inf.readEoln();
    }

    inf.readEof();
}
