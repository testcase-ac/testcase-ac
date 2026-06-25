#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "n");
    inf.readEoln();

    inf.readInt(-50000000, 50000000, "S");
    inf.readEoln();

    inf.readEof();
}
