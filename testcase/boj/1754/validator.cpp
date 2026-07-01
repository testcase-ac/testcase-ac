#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 20, "N");
    inf.readEoln();

    inf.readInt(0, n - 1, "K");
    inf.readEoln();

    inf.readInt(0, n - 1, "F");
    inf.readEoln();

    inf.readEof();
}
