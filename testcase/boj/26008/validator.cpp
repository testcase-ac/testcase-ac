#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5000000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 5000000, "M");
    inf.readSpace();
    int a = inf.readInt(1, 5000000, "A");
    inf.readEoln();

    int h = inf.readInt(0, m - 1, "H");
    inf.readEoln();

    (void)n;
    (void)a;
    (void)h;

    inf.readEof();
}
