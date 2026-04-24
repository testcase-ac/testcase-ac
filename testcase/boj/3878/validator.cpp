#include "testlib.h"
#include <set>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read counts of black and white points
        int n = inf.readInt(0, 100, "n");
        inf.readSpace();
        int m = inf.readInt(0, 100, "m");
        inf.readEoln();

        // Track all points to ensure no duplicates across black/white
        set<pair<int,int>> pts;

        // Read black points
        for (int i = 0; i < n; i++) {
            int x = inf.readInt(0, 10000, "x_black");
            inf.readSpace();
            int y = inf.readInt(0, 10000, "y_black");
            inf.readEoln();
            pair<int,int> p = make_pair(x, y);
            ensuref(!pts.count(p),
                    "Duplicate point in test case %d at black index %d: (%d, %d)",
                    tc, i, x, y);
            pts.insert(p);
        }

        // Read white points
        for (int i = 0; i < m; i++) {
            int x = inf.readInt(0, 10000, "x_white");
            inf.readSpace();
            int y = inf.readInt(0, 10000, "y_white");
            inf.readEoln();
            pair<int,int> p = make_pair(x, y);
            ensuref(!pts.count(p),
                    "Duplicate or overlapping point in test case %d at white index %d: (%d, %d)",
                    tc, i, x, y);
            pts.insert(p);
        }
    }

    inf.readEof();
    return 0;
}
