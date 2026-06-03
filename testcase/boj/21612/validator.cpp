#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(80, 200, "B");
    inf.readEoln();
    inf.readEof();
}
