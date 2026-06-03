#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "N");
    inf.readSpace();
    inf.readInt(1, 100, "W");
    inf.readSpace();
    inf.readInt(1, 100, "H");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(1, 1000, "match_length");
        inf.readEoln();
    }

    inf.readEof();
}
