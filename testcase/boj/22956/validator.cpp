#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "M");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    for (int row = 1; row <= n; ++row) {
        for (int col = 1; col <= m; ++col) {
            if (col > 1) {
                inf.readSpace();
            }
            inf.readInt(0, 1000, "H");
        }
        inf.readEoln();
    }

    for (int day = 1; day <= q; ++day) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, m, "b");
        inf.readSpace();
        inf.readInt(1, 100, "c");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
