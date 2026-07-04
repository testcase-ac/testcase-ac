#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 750, "N");
    inf.readEoln();

    for (int i = 0; i < 2 * n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readInt(0, 1, "output_bit");
    }
    inf.readEoln();

    inf.readEof();
    return 0;
}
