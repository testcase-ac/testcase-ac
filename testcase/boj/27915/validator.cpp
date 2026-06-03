#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    if (n > 1) {
        for (int i = 2; i <= n; ++i) {
            if (i > 2) {
                inf.readSpace();
            }
            inf.readInt(1, i - 1, "A_i");
        }
        inf.readEoln();
    }

    inf.readEof();
}
