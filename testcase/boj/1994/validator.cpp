#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(0, 999999999, "a_i");
        inf.readEoln();
    }

    inf.readEof();
}
