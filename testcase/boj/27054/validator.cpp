#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 8000, "N");
    inf.readEoln();

    for (int slot = 2; slot <= n; ++slot) {
        inf.readInt(0, slot - 1, "smaller_before");
        inf.readEoln();
    }

    inf.readEof();
}
