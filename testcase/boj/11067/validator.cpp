#include "testlib.h"
#include <set>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read n
        int n = inf.readInt(2, 100000, "n");
        inf.readEoln();

        // Read n cafe coordinates
        set<long long> seen;
        bool hasEntrance = false;
        const long long OFFSET = 1000000LL; // to separate x and y in key
        for (int i = 0; i < n; i++) {
            int x = inf.readInt(0, 100000, "x");
            inf.readSpace();
            int y = inf.readInt(-100000, 100000, "y");
            inf.readEoln();

            // Check for duplicate coordinates
            long long key = ( (long long)x + OFFSET ) << 20 | ( (long long)y + 200000 );
            ensuref(!seen.count(key),
                    "Duplicate cafe coordinate at index %d: (%d, %d)", i, x, y);
            seen.insert(key);

            // Check for entrance (0,0)
            if (x == 0 && y == 0) {
                hasEntrance = true;
            }
        }
        ensuref(hasEntrance, "No entrance cafe at (0,0)");

        // Read the query line: m and k_i's
        int m = inf.readInt(1, 10, "m");
        for (int i = 0; i < m; i++) {
            inf.readSpace();
            int k = inf.readInt(1, n, "k_i");
            (void)k;
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
