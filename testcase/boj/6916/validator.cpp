#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(0, 9, "digit");
    inf.readEoln();
    inf.readEof();
}
