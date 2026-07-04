#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(2, 500, "m");
    inf.readSpace();
    int n = inf.readInt(2, 500, "n");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            inf.readInt(-10000000, 10000000, "a_ij");
            if (j + 1 == n) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}
