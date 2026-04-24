#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of points
    int n = inf.readInt(3, 100000, "N");
    inf.readEoln();

    // To ensure no duplicate points
    set<pair<int,int>> pts;
    pts.clear();

    for (int i = 0; i < n; i++) {
        // Read coordinates
        int x = inf.readInt(1, 100000, "X_i");
        inf.readSpace();
        int y = inf.readInt(1, 100000, "Y_i");
        inf.readEoln();

        // Check for duplicates
        pair<int,int> p = make_pair(x, y);
        ensuref(!pts.count(p),
                "Duplicate point detected at index %d: (%d, %d)", 
                i+1, x, y);
        pts.insert(p);
    }

    inf.readEof();
    return 0;
}
