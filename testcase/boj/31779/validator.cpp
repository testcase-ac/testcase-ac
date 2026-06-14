#include "testlib.h"

#include <set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "m");
    inf.readSpace();
    int k = inf.readInt(0, n * m, "k");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readLongs(m, -1000000000LL, 1000000000LL, "a_i_j");
        inf.readEoln();
    }

    for (int i = 0; i < n; ++i) {
        inf.readLongs(m, -1000000000LL, 1000000000LL, "b_i_j");
        inf.readEoln();
    }

    set<pair<int, int>> volcanoes;
    for (int i = 0; i < k; ++i) {
        int x = inf.readInt(1, n, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, m, "y_i");
        inf.readEoln();

        ensuref(volcanoes.insert({x, y}).second,
                "duplicate volcano position at index %d: (%d, %d)", i + 1, x, y);
    }

    inf.readEof();
}
