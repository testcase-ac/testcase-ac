#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "N");
    inf.readSpace();
    int s = inf.readInt(1, 1000, "S");
    inf.readEoln();

    (void)n;
    (void)s;

    inf.readEof();
}
