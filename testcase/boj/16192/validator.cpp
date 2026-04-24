#include "testlib.h"
#include <set>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and q
    int n = inf.readInt(3, 2000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 250000, "q");
    inf.readEoln();

    // Read the set points P_i, ensure distinctness
    set<pair<int,int>> pts;
    for (int i = 0; i < n; i++) {
        int x = inf.readInt(-10000, 10000, "px");
        inf.readSpace();
        int y = inf.readInt(-10000, 10000, "py");
        inf.readEoln();
        pair<int,int> p = {x, y};
        ensuref(!pts.count(p),
                "Duplicate point at index %d: (%d, %d)", i+1, x, y);
        pts.insert(p);
    }

    // Read the queries Q_j
    for (int j = 0; j < q; j++) {
        int x = inf.readInt(-10000, 10000, "qx");
        inf.readSpace();
        int y = inf.readInt(-10000, 10000, "qy");
        inf.readEoln();
    }

    // Ensure no extra data
    inf.readEof();
    return 0;
}
