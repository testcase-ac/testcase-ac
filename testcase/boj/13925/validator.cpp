#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxN = 100000;
    const int maxM = 100000;
    const long long maxValue = 1000000000LL;

    int n = inf.readInt(1, maxN, "n");
    inf.readEoln();

    inf.readLongs(n, 1LL, maxValue, "a_i");
    inf.readEoln();

    int m = inf.readInt(1, maxM, "m");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int type = inf.readInt(1, 4, "query_type");
        inf.readSpace();
        int x = inf.readInt(1, n, "x");
        inf.readSpace();
        int y = inf.readInt(x, n, "y");

        if (type == 4) {
            inf.readEoln();
        } else {
            inf.readSpace();
            inf.readLong(1LL, maxValue, "v");
            inf.readEoln();
        }
    }

    inf.readEof();
}
