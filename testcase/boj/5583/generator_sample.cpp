#include "testlib.h"

#include <set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 14);
    int maxSkips = (n + 1) / 2;
    int m = rnd.next(0, maxSkips);

    vector<vector<pair<int, int>>> rows(n + 1);
    vector<set<int>> usedColumns(n + 1);

    int row = 0;
    int skipsUsed = 0;
    while (row < n) {
        int remaining = n - row;
        bool canSkip = skipsUsed < m && remaining >= 2;
        bool mustMoveOne = !canSkip || (m - skipsUsed >= remaining);
        int step = (!mustMoveOne && rnd.next(0, 99) < 45) ? 2 : 1;

        row += step;
        if (step == 2) {
            ++skipsUsed;
        }
        if (row <= n) {
            int x = rnd.next(1, 30);
            int d = rnd.next(1, 20);
            rows[row].push_back({x, d});
            usedColumns[row].insert(x);
        }
    }

    int densityMode = rnd.next(0, 3);
    for (int i = 1; i <= n; ++i) {
        int extraLimit = densityMode == 0 ? 1 : (densityMode == 1 ? 3 : 6);
        int target = rnd.next((int)rows[i].size(), extraLimit);
        if (rnd.next(0, 99) < 15) {
            target = 0;
        }
        target = max(target, (int)rows[i].size());
        target = min(target, 10);

        while ((int)rows[i].size() < target) {
            int x = rnd.next(1, 30);
            if (!usedColumns[i].insert(x).second) {
                continue;
            }
            int d = rnd.next(1, densityMode == 2 ? 1000 : 50);
            rows[i].push_back({x, d});
        }

        shuffle(rows[i].begin(), rows[i].end());
    }

    println(n, m);
    for (int i = 1; i <= n; ++i) {
        vector<int> line;
        line.push_back((int)rows[i].size());
        for (auto [x, d] : rows[i]) {
            line.push_back(x);
            line.push_back(d);
        }
        println(line);
    }

    return 0;
}
