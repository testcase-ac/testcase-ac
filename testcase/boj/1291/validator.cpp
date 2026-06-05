#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 2700, "N");
    inf.readEoln();
    inf.readEof();
}
