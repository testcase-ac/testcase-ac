#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 10, "a");
    inf.readSpace();
    inf.readInt(1, 10, "b");
    inf.readEoln();
    inf.readEof();
}
