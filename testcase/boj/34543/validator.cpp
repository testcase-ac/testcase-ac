#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(0, 5, "N");
    inf.readEoln();

    inf.readInt(0, 2000, "W");
    inf.readEoln();

    inf.readEof();
}
