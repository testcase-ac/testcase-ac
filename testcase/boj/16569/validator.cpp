#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(1, 100, "M");
    inf.readSpace();
    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int v = inf.readInt(1, min(5000, m * n), "V");
    inf.readEoln();

    int startX = inf.readInt(1, m, "X");
    inf.readSpace();
    int startY = inf.readInt(1, n, "Y");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            inf.readInt(0, 10000, "h_ij");
            if (j == n) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    set<pair<int, int>> volcanoes;
    for (int i = 1; i <= v; ++i) {
        int x = inf.readInt(1, m, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, n, "y_i");
        inf.readSpace();
        inf.readInt(0, 200, "t_i");
        inf.readEoln();

        ensuref(!(x == startX && y == startY),
                "start cell (%d, %d) must not contain a volcano", startX, startY);
        // CHECK: The statement describes V volcano locations and bounds V by M*N, so treat
        // volcano cells as distinct even though uniqueness is not stated as a separate sentence.
        ensuref(volcanoes.insert({x, y}).second,
                "duplicate volcano cell at volcano %d: (%d, %d)", i, x, y);
    }

    inf.readEof();
}
