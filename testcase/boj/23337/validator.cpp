#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(2, 300, "n");
    inf.readEoln();
    inf.readEof();
}
