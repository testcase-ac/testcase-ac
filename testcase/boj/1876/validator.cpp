#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    for (int i = 0; i < n; i++) {
        inf.readDouble(16.0, 18.0, "T");
        inf.readSpace();
        inf.readInt(10, 80, "X");
        inf.readEoln();
    }

    inf.readEof();
}
