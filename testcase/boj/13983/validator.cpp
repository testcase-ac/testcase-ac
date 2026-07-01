#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int k = inf.readInt(1, 20, "k");
    inf.readSpace();
    int r = inf.readInt(1, 1 << k, "r");
    inf.readEoln();
    inf.readEof();
}
