#include "testlib.h"
#include <set>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of sign posts
    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    // Read all points and check distinctness
    set<pair<int,int>> pts;
    for (int i = 0; i < n; i++) {
        int x = inf.readInt(-10000, 10000, "x_i");
        inf.readSpace();
        int y = inf.readInt(-10000, 10000, "y_i");
        inf.readEoln();
        pair<int,int> p = make_pair(x, y);
        ensuref(!pts.count(p),
                "Duplicate point detected at index %d: (%d, %d)", i, x, y);
        pts.insert(p);
    }

    inf.readEof();
    return 0;
}
