#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    inf.readInt(1, 10000, "a");
    inf.readSpace();
    inf.readInt(1, 10000, "b");
    inf.readEoln();
    inf.readEof();
    return 0;
}
