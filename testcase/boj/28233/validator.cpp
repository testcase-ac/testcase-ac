#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int i = inf.readInt(1, 2 * n, "i");
    inf.readSpace();
    int j = inf.readInt(1, 2 * n, "j");
    inf.readEoln();

    inf.readEof();
}
