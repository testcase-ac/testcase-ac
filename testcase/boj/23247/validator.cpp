#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(1, 300, "m");
    inf.readSpace();
    int n = inf.readInt(1, 300, "n");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            inf.readInt(1, 10, "p_ij");
            if (j + 1 < n) {
                inf.readSpace();
            }
        }
        inf.readEoln();
    }

    inf.readEof();
}
