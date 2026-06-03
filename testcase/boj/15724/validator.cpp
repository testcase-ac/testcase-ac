#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1024, "N");
    inf.readSpace();
    int m = inf.readInt(1, 1024, "M");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            inf.readInt(1, 100, "population");
        }
        inf.readEoln();
    }

    int k = inf.readInt(1, 100000, "K");
    inf.readEoln();

    for (int i = 0; i < k; ++i) {
        int x1 = inf.readInt(1, n, "x1");
        inf.readSpace();
        int y1 = inf.readInt(1, m, "y1");
        inf.readSpace();
        int x2 = inf.readInt(1, n, "x2");
        inf.readSpace();
        int y2 = inf.readInt(1, m, "y2");
        inf.readEoln();

        ensuref(x1 <= x2, "query %d has x1 > x2: %d > %d", i + 1, x1, x2);
        ensuref(y1 <= y2, "query %d has y1 > y2: %d > %d", i + 1, y1, y2);
    }

    inf.readEof();
    return 0;
}
