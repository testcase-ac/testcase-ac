#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 30, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(2, 1000, "N");
        inf.readEoln();

        int R = inf.readInt(1, 10000, "R");
        inf.readEoln();

        for (int i = 1; i <= R; ++i) {
            int A = inf.readInt(0, N - 1, "A");
            inf.readSpace();
            int B = inf.readInt(0, N - 1, "B");
            inf.readEoln();

            ensuref(A != B, "case %d road %d is a self-loop at city %d", tc, i, A);
        }
    }

    inf.readEof();
    return 0;
}
