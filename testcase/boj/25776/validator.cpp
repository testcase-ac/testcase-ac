#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 20, "n");
    inf.readSpace();
    int k = inf.readInt(1, n, "k");
    inf.readEoln();
    inf.readEof();
}
