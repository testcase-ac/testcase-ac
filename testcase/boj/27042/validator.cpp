#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 7100000, "N");
    inf.readEoln();
    inf.readEof();
}
