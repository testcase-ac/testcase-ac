#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(2, 200000, "N");
    inf.readEoln();
    inf.readEof();
}
