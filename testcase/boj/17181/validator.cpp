#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(4, 50, "n");
    inf.readSpace();
    int m = inf.readInt(4, 50, "m");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            inf.readInt(0, 34, "cell");
        }
        inf.readEoln();
    }

    inf.readEof();
}
