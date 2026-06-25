#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int p = inf.readInt(1, 100, "p");
    inf.readSpace();
    int q = inf.readInt(1, 100, "q");
    inf.readEoln();

    ensuref(q < p, "expected q < p, got q=%d and p=%d", q, p);
    (void)n;

    inf.readEof();
}
