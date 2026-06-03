#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(200, 239, "N");
    inf.readEoln();
    inf.readEof();
}
