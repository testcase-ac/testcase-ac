#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int k = inf.readInt(1, n, "K");
    inf.readSpace();
    inf.readInt(0, n - k, "E");
    inf.readEoln();
    inf.readEof();
}
