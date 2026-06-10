#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int h1 = inf.readInt(1, 100, "H1");
    inf.readSpace();
    int h2 = inf.readInt(h1, 100, "H2");
    inf.readSpace();
    inf.readInt(h2, 100, "H3");
    inf.readEoln();

    inf.readLong(1LL, 1000000000000LL, "N");
    inf.readEoln();

    inf.readEof();
    return 0;
}
