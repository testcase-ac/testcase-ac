#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 40, "N");
    inf.readEoln();

    inf.readInt(1, n, "K");
    inf.readEoln();

    inf.readEof();
}
