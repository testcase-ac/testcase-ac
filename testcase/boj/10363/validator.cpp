#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(3, 20000, "N");
        inf.readEoln();

        inf.readInts(N, 0, 1000000, "M_i");
        inf.readEoln();

        inf.readInt(0, 0, "P_1");
        for (int i = 2; i <= N; ++i) {
            inf.readSpace();
            inf.readInt(1, i - 1, "P_i");
        }
        inf.readEoln();
    }

    inf.readEof();
}
