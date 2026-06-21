#include "testlib.h"
#include <set>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseCount = 0;
    int totalPoints = 0;
    while (true) {
        int n = inf.readInt(0, 1000, "N");
        inf.readEoln();

        if (n == 0) {
            break;
        }

        ++caseCount;
        setTestCase(caseCount);
        ensuref(n >= 2, "N must be either 0 terminator or at least 2, found %d", n);

        // CHECK: the statement does not bound the number of test cases; cap total
        // points to keep repository validation inputs practical.
        totalPoints += n;
        ensuref(totalPoints <= 1000000, "too many points across test cases: %d", totalPoints);

        set<pair<int, int>> points;
        for (int i = 0; i < n; ++i) {
            int x = inf.readInt(-1000, 1000, "X");
            inf.readSpace();
            int y = inf.readInt(-1000, 1000, "Y");
            inf.readEoln();

            ensuref(points.insert({x, y}).second,
                    "duplicate point at case %d index %d: (%d, %d)",
                    caseCount, i + 1, x, y);
        }
    }

    inf.readEof();
    return 0;
}
