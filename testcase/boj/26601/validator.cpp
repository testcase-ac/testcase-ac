#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(0, 111222, "N");
    inf.readEoln();
    inf.readEof();
}
