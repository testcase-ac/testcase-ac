#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 300000, "N");
    inf.readSpace();
    int k = inf.readInt(2, n - 1, "K");
    inf.readEoln();

    inf.readEof();
}
