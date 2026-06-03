#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 1000000, "M");
    inf.readSpace();
    int t = inf.readInt(1, 100, "T");
    inf.readSpace();
    int k = inf.readInt(1, 1000000, "K");
    inf.readEoln();

    ensuref(k <= n, "K must be at most N: K=%d, N=%d", k, n);
    ensuref(k <= m, "K must be at most M: K=%d, M=%d", k, m);

    set<pair<int, int>> points;
    for (int i = 0; i < t; ++i) {
        int a = inf.readInt(0, n, "A_i");
        inf.readSpace();
        int b = inf.readInt(0, m, "B_i");
        inf.readEoln();

        ensuref(points.insert({a, b}).second,
                "duplicate jewel coordinate at index %d: (%d, %d)", i + 1, a, b);
    }

    inf.readEof();
}
