#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(2, (1 << 20) - 1, "N");
    inf.readSpace();
    int Q = inf.readInt(1, 200000, "Q");
    inf.readEoln();

    for (int i = 1; i <= Q; ++i) {
        inf.readInt(2, N, "x_i");
        inf.readEoln();
    }

    inf.readEof();
}
