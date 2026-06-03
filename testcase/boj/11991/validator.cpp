#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(1, 1000000000, "A");
    inf.readSpace();
    int b = inf.readInt(1, 1000000000, "B");
    inf.readSpace();
    int n = inf.readInt(0, 25000, "n");
    inf.readSpace();
    int m = inf.readInt(0, 25000, "m");
    inf.readEoln();

    set<int> vertical;
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(0, 1000000000, "a_i");
        inf.readEoln();
        ensuref(0 < x && x < a,
                "vertical fence coordinate at index %d is outside (0, A): %d", i + 1, x);
        ensuref(vertical.insert(x).second,
                "duplicate vertical fence coordinate at index %d: %d", i + 1, x);
    }

    set<int> horizontal;
    for (int i = 0; i < m; ++i) {
        int y = inf.readInt(0, 1000000000, "b_i");
        inf.readEoln();
        ensuref(0 < y && y < b,
                "horizontal fence coordinate at index %d is outside (0, B): %d", i + 1, y);
        ensuref(horizontal.insert(y).second,
                "duplicate horizontal fence coordinate at index %d: %d", i + 1, y);
    }

    inf.readEof();
}
