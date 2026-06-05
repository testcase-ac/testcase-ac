#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "M");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            inf.readInt(0, 100000000, "cell");
            if (j < m) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readInt(1, 100000000, "H");
    inf.readEoln();
    inf.readEof();
}
