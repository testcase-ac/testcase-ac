#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 200000, "n");
    inf.readSpace();
    int k = inf.readInt(2, n - 1, "k");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int a = inf.readInt(0, 1, "a_i");
        if (i < n) {
            inf.readSpace();
        } else {
            ensuref(a == 1, "a_n must be 1");
            inf.readEoln();
        }
    }

    inf.readEof();
}
