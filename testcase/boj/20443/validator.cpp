#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(4, 100, "N");
    inf.readEoln();
    inf.readEof();
}
