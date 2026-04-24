#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of points
    int n = inf.readInt(1, 70000, "n");
    inf.readEoln();

    // Read points and ensure they are distinct
    set<pair<int,int>> pts;
    for (int i = 0; i < n; i++) {
        int x = inf.readInt(0, 100000, "x_i");
        inf.readSpace();
        int y = inf.readInt(0, 100000, "y_i");
        inf.readEoln();

        pair<int,int> p = make_pair(x, y);
        ensuref(!pts.count(p),
                "Duplicate point detected at index %d: (%d, %d)",
                i, x, y);
        pts.insert(p);
    }

    // No more input
    inf.readEof();
    return 0;
}
