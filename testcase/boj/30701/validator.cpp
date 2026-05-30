#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    inf.readInt(1, 1000000000, "D");
    inf.readEoln();

    for (int i = 0; i < N; ++i) {
        inf.readInt(1, 2, "A_i");
        inf.readSpace();
        inf.readInt(2, 1000000000, "X_i");
        inf.readEoln();
    }

    inf.readEof();
}
