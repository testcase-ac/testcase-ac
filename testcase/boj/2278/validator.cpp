#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    inf.readInt(1, 1000, "M");
    inf.readEoln();

    for (int i = 1; i <= n - 1; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            inf.readInt(1, 500, "d_ij");
            if (j < n) {
                inf.readSpace();
            }
        }
        inf.readEoln();
    }

    inf.readEof();
}
