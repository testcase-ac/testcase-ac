#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 20, "N");
    inf.readEoln();

    for (int i = 1; i <= n - 1; ++i) {
        inf.readInt(1, 5000, "small_jump");
        inf.readSpace();
        inf.readInt(1, 5000, "big_jump");
        inf.readEoln();
    }

    inf.readInt(1, 5000, "K");
    inf.readEoln();
    inf.readEof();
}
