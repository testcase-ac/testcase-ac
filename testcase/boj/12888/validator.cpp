#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(0, 60, "H");
    inf.readEoln();
    inf.readEof();
}
