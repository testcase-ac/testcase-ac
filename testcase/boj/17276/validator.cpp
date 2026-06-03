#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 499, "n");
        inf.readSpace();
        int d = inf.readInt(-360, 360, "d");
        inf.readEoln();

        ensuref(n % 2 == 1, "n must be odd, got %d", n);
        ensuref(d % 45 == 0, "d must be a multiple of 45, got %d", d);

        for (int row = 1; row <= n; ++row) {
            for (int col = 1; col <= n; ++col) {
                inf.readInt(1, 1000000, "x");
                if (col < n) {
                    inf.readSpace();
                } else {
                    inf.readEoln();
                }
            }
        }
    }

    inf.readEof();
    return 0;
}
