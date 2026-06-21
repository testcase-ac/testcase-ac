#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 1000, "b");
    inf.readSpace();
    inf.readInt(1, 1000, "w");
    inf.readEoln();

    inf.readEof();
    return 0;
}
