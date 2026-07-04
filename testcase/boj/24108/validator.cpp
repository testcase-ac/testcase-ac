#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int k = inf.readInt(1, 100000, "K");
    inf.readSpace();
    int n = inf.readInt(1, 10000000, "N");
    inf.readSpace();
    int m = inf.readInt(0, n, "M");
    inf.readEoln();

    int maxCurrentScore = 100 * m;
    for (int i = 1; i <= k; ++i) {
        inf.readInt(0, maxCurrentScore, "P_i");
        inf.readEoln();
    }

    inf.readEof();
}
