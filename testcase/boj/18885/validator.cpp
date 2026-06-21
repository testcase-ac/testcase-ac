#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    long long totalLength = 0;
    for (int i = 1; i <= n; ++i) {
        int l = inf.readInt(1, 100000, "l_i");
        totalLength += l;
        ensuref(totalLength <= 100000, "sum of l_i exceeds 100000 at sequence %d", i);

        for (int j = 1; j <= l; ++j) {
            inf.readSpace();
            inf.readInt(0, 1000000, "s_i_j");
        }
        inf.readEoln();
    }

    inf.readEof();
}
