#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300, "N");
    inf.readEoln();

    for (int row = 1; row <= n; ++row) {
        for (int col = 1; col <= n; ++col) {
            if (col > 1) {
                inf.readSpace();
            }
            inf.readInt(1, 10, "A_ij");
        }
        inf.readEoln();
    }

    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        int x1 = inf.readInt(1, n, "x1");
        inf.readSpace();
        int y1 = inf.readInt(1, n, "y1");
        inf.readSpace();
        int x2 = inf.readInt(x1, n, "x2");
        inf.readSpace();
        inf.readInt(y1, n, "y2");
        inf.readEoln();
    }

    inf.readEof();
}
