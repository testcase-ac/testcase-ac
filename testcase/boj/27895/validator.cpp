#include "testlib.h"

#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 2000, "M");
    inf.readSpace();
    int k = inf.readInt(0, 500000, "K");
    inf.readEoln();

    long long cells = 1LL * n * m;
    ensuref(k <= min((cells - 2) / 2, 500000LL),
            "K=%d exceeds portal-pair limit for %d by %d grid", k, n, m);

    vector<string> grid(m);
    int portal_count = 0;
    for (int y = 0; y < m; ++y) {
        grid[y] = inf.readToken("[01P]{1,2000}", "row");
        inf.readEoln();
        ensuref((int)grid[y].size() == n, "row %d has length %d, expected %d",
                y + 1, (int)grid[y].size(), n);
        for (char c : grid[y]) {
            if (c == 'P') {
                ++portal_count;
            }
        }
    }

    ensuref(grid[0][0] == '0', "cell (0,0) must be empty");
    ensuref(grid[m - 1][n - 1] == '0', "cell (N-1,M-1) must be empty");
    ensuref(portal_count == 2 * k, "grid has %d portals, expected %d",
            portal_count, 2 * k);

    set<pair<int, int>> used_portals;
    for (int i = 0; i < k; ++i) {
        int x1 = inf.readInt(0, n - 1, "x1");
        inf.readSpace();
        int y1 = inf.readInt(0, m - 1, "y1");
        inf.readSpace();
        int x2 = inf.readInt(0, n - 1, "x2");
        inf.readSpace();
        int y2 = inf.readInt(0, m - 1, "y2");
        inf.readEoln();

        ensuref(x1 != x2 || y1 != y2,
                "portal pair %d uses the same coordinate twice", i + 1);
        ensuref(grid[y1][x1] == 'P',
                "portal pair %d first coordinate (%d,%d) is not P", i + 1, x1, y1);
        ensuref(grid[y2][x2] == 'P',
                "portal pair %d second coordinate (%d,%d) is not P", i + 1, x2, y2);
        ensuref(used_portals.insert({x1, y1}).second,
                "portal coordinate (%d,%d) appears more than once", x1, y1);
        ensuref(used_portals.insert({x2, y2}).second,
                "portal coordinate (%d,%d) appears more than once", x2, y2);
    }

    inf.readEof();
}
