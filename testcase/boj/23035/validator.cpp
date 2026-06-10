#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxCoord = 1000000000;

    int n = inf.readInt(0, maxCoord, "N");
    inf.readSpace();
    int m = inf.readInt(0, maxCoord, "M");
    inf.readEoln();

    int t = inf.readInt(0, 100000, "T");
    inf.readEoln();

    set<pair<int, int>> seen;
    for (int i = 0; i < t; ++i) {
        int r = inf.readInt(0, maxCoord, "r");
        inf.readSpace();
        int c = inf.readInt(0, maxCoord, "c");
        inf.readEoln();

        ensuref(seen.emplace(r, c).second,
                "duplicate cat coordinate at index %d: (%d, %d)", i + 1, r, c);
    }

    inf.readEof();
}
