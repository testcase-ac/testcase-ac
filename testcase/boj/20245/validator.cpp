#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "n");
    inf.readSpace();
    inf.readInt(0, 2 * n, "k");
    inf.readEoln();
    inf.readEof();
}
