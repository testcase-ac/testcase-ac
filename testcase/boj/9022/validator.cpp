#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // Number of stains in this test case
        int n = inf.readInt(1, 10000, "n");
        inf.readEoln();

        // Read each stain, ensure distinctness and y != 0
        set<pair<int,int>> seen;
        for (int i = 0; i < n; ++i) {
            int x = inf.readInt(-1000000, 1000000, "x");
            inf.readSpace();
            int y = inf.readInt(-1000000, 1000000, "y");
            inf.readEoln();

            // No stain on the x-axis
            ensuref(y != 0,
                    "Stain #%d is on the x-axis: (%d, %d)",
                    i+1, x, y);

            // All stains must be distinct
            pair<int,int> p = {x, y};
            ensuref(!seen.count(p),
                    "Duplicate stain at index %d: (%d, %d)",
                    i+1, x, y);
            seen.insert(p);
        }
    }

    inf.readEof();
    return 0;
}
