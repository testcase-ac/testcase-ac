#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 500, "N");
    inf.readSpace();
    int q = inf.readInt(1, 200000, "Q");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (j > 1) {
                inf.readSpace();
            }
            inf.readInt(0, 10000, "A_ij");
        }
        inf.readEoln();
    }

    for (int i = 1; i <= q; ++i) {
        int sx = inf.readInt(1, n, "S_x");
        inf.readSpace();
        inf.readInt(1, n, "S_y");
        inf.readSpace();
        int l = inf.readInt(0, n - 1, "L");
        inf.readEoln();

        ensuref(l < sx, "query %d has L >= S_x: L=%d, S_x=%d", i, l, sx);
    }

    inf.readEof();
    return 0;
}
