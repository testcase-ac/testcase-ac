#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int y = inf.readInt(0, 200, "Y");
    inf.readEoln();

    for (int i = 0; i < y; ++i) {
        inf.readInt(0, n - 1, "k");
        inf.readEoln();
    }

    inf.readEof();
}
