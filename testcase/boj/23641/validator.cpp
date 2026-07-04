#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readEoln();

    inf.readInt(1, 100000, "a_1");
    for (int i = 2; i <= n; ++i) {
        inf.readSpace();
        inf.readInt(1, 100000, "a_i");
    }
    inf.readEoln();
    inf.readEof();
}
