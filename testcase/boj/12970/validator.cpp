#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 50, "N");
    inf.readSpace();
    int k = inf.readInt(0, n * (n - 1) / 2, "K");
    inf.readEoln();
    inf.readEof();
}
