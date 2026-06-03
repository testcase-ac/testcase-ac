#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5000, "n");
    inf.readEoln();

    inf.readInts(n, 0, 9, "t_i");
    inf.readEoln();
    inf.readEof();
}
