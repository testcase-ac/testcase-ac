#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 100, "n");
    inf.readSpace();
    inf.readInt(1, 100, "k");
    inf.readEoln();
    inf.readEof();
}
