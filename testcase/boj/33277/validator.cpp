#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(638, 641, "N");
    inf.readSpace();
    int m = inf.readInt(0, n, "M");
    inf.readEoln();
    inf.readEof();
}
