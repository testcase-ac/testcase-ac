#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100, "m");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            inf.readInt(0, 1, "cell");
            if (j + 1 < m) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
}
