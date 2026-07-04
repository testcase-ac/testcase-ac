#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(2, 100, "a");
    inf.readSpace();
    inf.readInt(2, 100, "b");
    inf.readEoln();
    inf.readEof();
}
