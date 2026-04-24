#include "testlib.h"
#include <set>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 2000000, "K");
    inf.readEoln();

    // To check for distinct (x, y) pairs
    set<pair<int, int>> coords;

    for (int i = 0; i < N; ++i) {
        int g_i = inf.readInt(1, 10000, "g_i");
        inf.readSpace();
        int x_i = inf.readInt(0, 1000000, "x_i");
        inf.readSpace();
        int y_i = inf.readInt(0, 1000000, "y_i");
        inf.readEoln();

        pair<int, int> p = make_pair(x_i, y_i);
        ensuref(coords.count(p) == 0, "Duplicate patch position at index %d: (%d, %d)", i + 1, x_i, y_i);
        coords.insert(p);
    }

    inf.readEof();
}
