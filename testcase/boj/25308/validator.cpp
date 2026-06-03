#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    for (int i = 1; i <= 8; ++i) {
        inf.readInt(1, 10000, format("a_%d", i));
        if (i == 8) {
            inf.readEoln();
        } else {
            inf.readSpace();
        }
    }

    inf.readEof();
}
