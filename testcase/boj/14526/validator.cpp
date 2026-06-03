#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(0, n, "color");
        inf.readEoln();
    }

    inf.readEof();
}
