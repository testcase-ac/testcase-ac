#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(1, 1000000, "A");
        inf.readSpace();
        int b = inf.readInt(1, 1000000, "B");
        inf.readSpace();
        int c = inf.readInt(b, 1000000, "C");
        inf.readEoln();
    }

    inf.readEof();
}
