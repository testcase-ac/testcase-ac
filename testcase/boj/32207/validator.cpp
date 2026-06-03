#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "M");
    inf.readSpace();
    inf.readInt(1, 5, "K");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (j > 1) {
                inf.readSpace();
            }
            inf.readInt(0, 1000, "A_ij");
        }
        inf.readEoln();
    }

    inf.readEof();
}
