#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "k");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            inf.readInt(0, 1, "a_ij");
            if (j + 1 < n) {
                inf.readSpace();
            }
        }
        inf.readEoln();
    }

    inf.readEof();
}
