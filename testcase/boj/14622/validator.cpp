#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 100000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(0, 4999999, "daewoong_i");
        inf.readSpace();
        inf.readInt(0, 4999999, "gyuseong_i");
        inf.readEoln();
    }

    inf.readEof();
}
