#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 20, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(1, 100, "s_i");
        inf.readEoln();
    }

    inf.readEof();
}
