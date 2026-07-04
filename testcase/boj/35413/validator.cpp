#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    inf.readInt(0, n + 1, "K");
    inf.readEoln();

    inf.readEof();
}
