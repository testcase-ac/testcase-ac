#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no T bound; testcase.ac defaults cap unstated case counts.
    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    int totalPoints = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(4, 3000, "n");
        inf.readEoln();
        totalPoints += n;
        // CHECK: Practical cap for unstated total input size; 2,000,000 points is about 4,000,000 coordinate tokens.
        ensuref(totalPoints <= 2000000, "total number of points exceeds practical cap");

        set<pair<int, int>> points;
        for (int i = 0; i < n; ++i) {
            int x = inf.readInt(-10000, 10000, "x");
            inf.readSpace();
            int y = inf.readInt(-10000, 10000, "y");
            inf.readEoln();

            ensuref(points.insert({x, y}).second,
                    "duplicate point in testcase %d at index %d: (%d, %d)",
                    tc,
                    i + 1,
                    x,
                    y);
        }
    }

    inf.readEof();
}
