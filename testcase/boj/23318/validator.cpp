#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 20, "n");
    inf.readSpace();
    int m = inf.readInt(2, 8, "m");
    inf.readEoln();

    int a = inf.readInt(1, n - 1, "a");
    inf.readSpace();
    int b = inf.readInt(1, m - 1, "b");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            inf.readInt(1, 15, "cell");
        }
        inf.readEoln();
    }

    inf.readEof();
}
