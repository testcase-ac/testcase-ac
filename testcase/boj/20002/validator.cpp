#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            inf.readInt(-1000, 1000, "profit");
            if (j + 1 == n) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}
