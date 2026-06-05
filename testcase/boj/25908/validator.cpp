#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int s = inf.readInt(1, 10000000, "S");
    inf.readSpace();
    inf.readInt(s, 10000000, "T");
    inf.readEoln();

    inf.readEof();
}
