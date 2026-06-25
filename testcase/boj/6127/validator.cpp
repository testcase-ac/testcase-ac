#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int k = inf.readInt(1, 100000, "K");
    inf.readEoln();

    for (int i = 1; i <= k; ++i) {
        inf.readInt(1, n, "R_i");
        inf.readSpace();
        inf.readInt(1, n, "C_i");
        inf.readEoln();
    }

    // CHECK: The statement lists opponent locations but does not require them to be distinct.
    inf.readEof();
}
