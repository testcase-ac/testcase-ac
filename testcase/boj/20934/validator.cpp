#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 5, "c_i");
        if (i == n) {
            inf.readEoln();
        } else {
            inf.readSpace();
        }
    }

    inf.readEof();
}
