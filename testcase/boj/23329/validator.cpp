#include "testlib.h"

#include <set>
#include <string>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int s = inf.readInt(1, n, "s");
    inf.readSpace();
    int e = inf.readInt(1, n, "e");
    inf.readEoln();

    ensuref(s != e, "s and e must be different: %d", s);

    set<pair<int, int>> coordinates;
    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(1, 1000000000, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, 1000000000, "y_i");
        inf.readSpace();
        inf.readInt(0, 200000, "c_i");
        inf.readSpace();
        inf.readToken("N|NE|E|SE|S|SW|W|NW", "d_i");
        inf.readEoln();

        ensuref(coordinates.insert({x, y}).second,
                "duplicate coordinates at launcher %d: (%d, %d)", i, x, y);
    }

    inf.readEof();
    return 0;
}
