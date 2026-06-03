#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: BOJ 1760's Korean statement gives 1 <= N, M <= 100.
    // The legacy English variant says 200, but this problem entry follows BOJ 1760.
    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100, "M");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            inf.readInt(0, 2, "cell");
            if (j < m) {
                inf.readSpace();
            }
        }
        inf.readEoln();
    }

    inf.readEof();
}
