#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(2, 500, "N");
    inf.readEoln();
    inf.readEof();
}
