#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(1, 100000, "N");
        inf.readSpace();
        int M = inf.readInt(1, 100000, "M");
        inf.readEoln();

        inf.readInts(N, 1, 1000000000, "x_i");
        inf.readEoln();

        for (int j = 0; j < M; ++j) {
            int y = inf.readInt(1, 1000000000, "y_j");
            inf.readSpace();
            int z = inf.readInt(1, 1000000000, "z_j");
            inf.readEoln();
            ensuref(y <= z, "driver %d has y_j (%d) > z_j (%d)", j + 1, y, z);
        }
    }

    inf.readEof();
    return 0;
}
