#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10, "N");
    inf.readSpace();
    int m = inf.readInt(1, 10000, "M");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            inf.readInt(-100, 100, "a_ij");
        }
        inf.readEoln();
    }

    inf.readEof();
}
