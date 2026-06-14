#include "testlib.h"
#include <set>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 26, "N");
    inf.readSpace();
    int m = inf.readInt(2 * n - 1, 100000, "M");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    set<pair<int, int>> intervals;
    for (int i = 1; i <= q; ++i) {
        int s = inf.readInt(1, m, "s_i");
        inf.readSpace();
        int e = inf.readInt(1, m, "e_i");
        inf.readEoln();

        ensuref(s <= e, "interval %d has s_i > e_i: %d > %d", i, s, e);
        int width = e - s + 1;
        ensuref(width >= 2 * n - 1,
                "interval %d width is too small: %d < %d", i, width, 2 * n - 1);
        ensuref(width % 2 == 1, "interval %d width is even: %d", i, width);
        ensuref(intervals.emplace(s, e).second,
                "duplicate interval at index %d: (%d, %d)", i, s, e);
    }

    inf.readEof();
}
