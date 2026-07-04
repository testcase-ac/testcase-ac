#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int L = inf.readInt(1, 100000000, "L");
    inf.readSpace();
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    set<pair<int, int>> guards;
    for (int i = 1; i <= N; ++i) {
        int x = inf.readInt(0, L - 1, "x_i");
        inf.readSpace();
        int y = inf.readInt(0, L - 1, "y_i");
        inf.readEoln();

        ensuref(guards.emplace(x, y).second,
                "duplicate guard position at index %d: (%d, %d)", i, x, y);
    }

    inf.readEof();
}
