#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(0, 2, "t");
    inf.readEoln();
    inf.readEof();
}
