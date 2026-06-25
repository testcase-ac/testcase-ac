#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 50000, "N");
    inf.readSpace();
    inf.readInt(1, N, "M");
    inf.readSpace();
    inf.readInt(0, 5000, "D");
    inf.readSpace();
    inf.readInt(1, 1000000, "L");
    inf.readEoln();

    for (int i = 1; i <= N; ++i) {
        inf.readInt(1, 1000000, format("S_%d", i));
        inf.readEoln();
    }

    inf.readEof();
}
