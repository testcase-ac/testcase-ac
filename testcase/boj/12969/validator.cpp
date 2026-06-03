#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 30, "N");
    inf.readSpace();
    int k = inf.readInt(0, n * (n - 1) / 2, "K");
    inf.readEoln();
    inf.readEof();
}
