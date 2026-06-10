#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 10000000, "N");
    inf.readSpace();
    inf.readInt(1, n - 1, "K");
    inf.readEoln();

    inf.readEof();
    return 0;
}
