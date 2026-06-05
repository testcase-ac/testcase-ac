#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(2, 99, "N");
    inf.readEoln();
    inf.readEof();
}
