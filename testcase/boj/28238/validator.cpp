#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= 5; ++j) {
            inf.readInt(0, 1, format("a[%d][%d]", i, j));
            if (j < 5) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
}
