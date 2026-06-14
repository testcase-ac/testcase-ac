#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(3, 200000, "M");
    inf.readEoln();
    inf.readEof();
}
