#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100, "M");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            inf.readInt(1, 10000, "A_ij");
            if (j == m) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}
