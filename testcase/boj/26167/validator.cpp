#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(6, 500, "N");
    inf.readSpace();
    int m = inf.readInt(6, 500, "M");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            inf.readInt(1, 1000, "cell");
        }
        inf.readEoln();
    }

    inf.readEof();
}
