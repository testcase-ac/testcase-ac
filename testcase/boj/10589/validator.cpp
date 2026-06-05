#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "n");
    inf.readSpace();
    int m = inf.readInt(1, 50, "m");
    inf.readEoln();

    inf.readEof();
}
