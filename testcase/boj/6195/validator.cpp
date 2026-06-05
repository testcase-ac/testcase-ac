#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 20000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(1, 50000, "L_i");
        inf.readEoln();
    }

    inf.readEof();
}
