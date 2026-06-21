#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 2000, "N");
    inf.readEoln();

    for (int row = 1; row <= n; ++row) {
        for (int col = 1; col <= n; ++col) {
            inf.readInt(0, 1, "pixel");
            if (col < n) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
}
