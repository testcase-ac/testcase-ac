#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(171, 171, "M");
    inf.readEoln();

    inf.readEof();
    return 0;
}
