#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 20, "N");
    inf.readSpace();
    // CHECK: The statement bounds N and P independently, so P > N is valid
    // input even though no selection can satisfy it.
    int p = inf.readInt(1, 20, "P");
    inf.readSpace();
    int e = inf.readInt(1, 1000000, "E");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(1, 1000000, "x_i");
        inf.readSpace();
        int y = inf.readInt(x, 1000000, "y_i");
        inf.readEoln();
    }

    inf.readEof();
}
