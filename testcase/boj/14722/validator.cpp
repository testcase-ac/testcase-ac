#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    for (int row = 1; row <= n; ++row) {
        for (int col = 1; col <= n; ++col) {
            inf.readInt(0, 2, "milk");
            if (col == n) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}
