#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read number of points
        int n = inf.readInt(4, 10000, "n");
        inf.readEoln();

        // Check distinctness of points
        set<pair<int,int>> seen;
        for (int i = 0; i < n; i++) {
            int x = inf.readInt(-1000000, 1000000, "x");
            inf.readSpace();
            int y = inf.readInt(-1000000, 1000000, "y");
            inf.readEoln();
            pair<int,int> p = make_pair(x, y);
            ensuref(!seen.count(p),
                    "Duplicate point detected at (%d, %d)", x, y);
            seen.insert(p);
        }
    }

    inf.readEof();
    return 0;
}
