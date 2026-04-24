#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and q
    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "q");
    inf.readEoln();

    // Read trees, ensure distinct locations
    set<pair<int,int>> seen;
    for (int i = 0; i < n; i++) {
        int x = inf.readInt(1, 1000000000, "x");
        inf.readSpace();
        int y = inf.readInt(1, 1000000000, "y");
        inf.readSpace();
        int h = inf.readInt(1, 1000000000, "h");
        inf.readEoln();

        // Check distinct coordinates
        pair<int,int> p = make_pair(x, y);
        ensuref(!seen.count(p),
                "Duplicate tree location at index %d: (%d, %d)", 
                i, x, y);
        seen.insert(p);
    }

    // Read queries
    for (int i = 0; i < q; i++) {
        int x_low  = inf.readInt(1, 1000000000, "x_low");
        inf.readSpace();
        int y_low  = inf.readInt(1, 1000000000, "y_low");
        inf.readSpace();
        int x_high = inf.readInt(1, 1000000000, "x_high");
        inf.readSpace();
        int y_high = inf.readInt(1, 1000000000, "y_high");
        inf.readEoln();

        // Check rectangular bounds
        ensuref(x_low <= x_high,
                "In query %d: x_low (%d) > x_high (%d)", 
                i, x_low, x_high);
        ensuref(y_low <= y_high,
                "In query %d: y_low (%d) > y_high (%d)", 
                i, y_low, y_high);
    }

    inf.readEof();
    return 0;
}
