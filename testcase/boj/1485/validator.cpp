#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases (not specified => assume up to 100000)
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);
        set<pair<int,int>> pts;

        // Each test case has exactly 4 points
        for (int i = 0; i < 4; i++) {
            int x = inf.readInt(-100000, 100000, "x");
            inf.readSpace();
            int y = inf.readInt(-100000, 100000, "y");
            inf.readEoln();

            // No duplicate points
            ensuref(pts.count({x, y}) == 0,
                    "Duplicate point in test case %d: (%d, %d)", tc, x, y);
            pts.insert({x, y});
        }
    }

    inf.readEof();
    return 0;
}
