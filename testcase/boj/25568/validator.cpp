#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    for (int row = 1; row <= n; ++row) {
        for (int col = 1; col <= row; ++col) {
            inf.readInt(0, 2, "color");
            if (col == row) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
    return 0;
}
