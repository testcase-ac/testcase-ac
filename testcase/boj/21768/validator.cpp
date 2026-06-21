#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(0, 20, "N");
    inf.readEoln();

    int length = 1 << n;
    for (int i = 0; i < length; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readInt(0, 10000000, "A_i");
    }
    inf.readEoln();
    inf.readEof();
}
