#include "testlib.h"

#include <set>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 1000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (j > 1) {
                inf.readSpace();
            }
            inf.readInt(1, 2, "m_ij");
        }
        inf.readEoln();
    }

    int p = inf.readInt(1, n * n - 2, "P");
    inf.readEoln();

    set<pair<int, int>> points;
    for (int i = 1; i <= p; ++i) {
        int r = inf.readInt(1, n, "r_i");
        inf.readSpace();
        int c = inf.readInt(1, n, "c_i");
        inf.readEoln();

        ensuref(!(r == 1 && c == 1), "point %d is the start cell", i);
        ensuref(!(r == n && c == n), "point %d is the end cell", i);
        ensuref(points.insert({r, c}).second,
                "duplicate point at index %d: (%d, %d)", i, r, c);
    }

    inf.readEof();
}
