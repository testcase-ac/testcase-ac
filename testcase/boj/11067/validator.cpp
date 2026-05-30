#include "testlib.h"
#include <algorithm>
#include <map>
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        int n = inf.readInt(2, 100000, "n");
        inf.readEoln();

        set<pair<int, int>> seen;
        map<int, vector<int>> ysByX;
        bool hasEntrance = false;
        for (int i = 0; i < n; i++) {
            int x = inf.readInt(0, 100000, "x");
            inf.readSpace();
            int y = inf.readInt(-100000, 100000, "y");
            inf.readEoln();

            ensuref(seen.insert({x, y}).second,
                    "duplicate cafe coordinate at index %d: (%d, %d)", i + 1, x, y);
            ysByX[x].push_back(y);
            if (x == 0 && y == 0) {
                hasEntrance = true;
            }
        }
        ensuref(hasEntrance, "No entrance cafe at (0,0)");

        int currentY = 0;
        for (auto& [x, ys] : ysByX) {
            sort(ys.begin(), ys.end());
            ensuref(ys.front() == currentY || ys.back() == currentY,
                    "x=%d vertical cafe group cannot be reached from y=%d", x, currentY);
            currentY = (ys.front() == currentY) ? ys.back() : ys.front();
        }

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
