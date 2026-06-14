#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(1, 8, "M");
    inf.readSpace();
    int n = inf.readInt(1, 8, "N");
    inf.readEoln();

    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < m; ++col) {
            inf.readInt(1, 5, "c");
            if (col + 1 == m) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}
