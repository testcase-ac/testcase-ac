#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 199, "n");
    inf.readSpace();
    int k = inf.readInt(2, 99, "k");
    inf.readEoln();

    inf.readEof();
}
