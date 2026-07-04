#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "n");
    inf.readSpace();
    inf.readInt(1, 2000, "k");
    inf.readEoln();

    inf.readToken("[DG]{1,2000}", "s");
    inf.readEoln();

    inf.readEof();
    return 0;
}
