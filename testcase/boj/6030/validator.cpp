#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int p = inf.readInt(1, 6000, "P");
    inf.readSpace();
    int q = inf.readInt(1, 6000, "Q");
    inf.readEoln();
    inf.readEof();

    (void)p;
    (void)q;
}
