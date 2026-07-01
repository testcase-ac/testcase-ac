#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    for (int i = 1; i <= 3; ++i) {
        inf.readInt(1, 100, format("w%d", i));
        inf.readSpace();
        inf.readInt(1, 100, format("h%d", i));
        inf.readEoln();
    }

    inf.readEof();
}
