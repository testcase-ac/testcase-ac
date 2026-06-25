#include "testlib.h"
#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    int k = 1;
    vector<pair<int, int>> points;

    auto add = [&](int x, int y) {
        points.push_back({x, y});
    };

    if (mode == 0) {
        n = rnd.next(1, 12);
        int maxM = min(n * n, 45);
        int m = rnd.next(1, maxM);
        k = rnd.next(1, max(1, n));

        vector<pair<int, int>> cells;
        for (int x = 1; x <= n; ++x) {
            for (int y = 1; y <= n; ++y) {
                cells.push_back({x, y});
            }
        }
        shuffle(cells.begin(), cells.end());
        points.assign(cells.begin(), cells.begin() + m);
    } else if (mode == 1) {
        n = rnd.next(2, 9);
        int side = rnd.next(2, n);
        k = rnd.next(1, side - 1);
        for (int x = 1; x <= side; ++x) {
            for (int y = 1; y <= side; ++y) {
                add(x, y);
            }
        }
    } else if (mode == 2) {
        n = rnd.next(4, 18);
        k = rnd.next(1, 3);
        int rows = rnd.next(2, min(n, 7));
        int cols = rnd.next(2, min(n, 7));
        for (int x = 1; x <= rows; ++x) {
            int cnt = rnd.next(1, min(cols, k + 2));
            vector<int> ys;
            for (int y = 1; y <= cols; ++y) ys.push_back(y);
            shuffle(ys.begin(), ys.end());
            for (int i = 0; i < cnt; ++i) add(x, ys[i]);
        }
    } else if (mode == 3) {
        n = rnd.next(5, 20);
        k = rnd.next(1, 4);
        int len = rnd.next(3, min(n, 10));
        for (int i = 1; i <= len; ++i) {
            add(i, i);
            if (i + 1 <= len) add(i, i + 1);
        }
        for (int i = 0; i < rnd.next(0, min(8, n)); ++i) {
            add(rnd.next(1, n), rnd.next(1, n));
        }
    } else if (mode == 4) {
        n = rnd.next(10, 200000);
        k = rnd.next(n / 2, n);
        int m = rnd.next(1, 20);
        set<pair<int, int>> used;
        while ((int)used.size() < m) {
            used.insert({rnd.next(1, n), rnd.next(1, n)});
        }
        points.assign(used.begin(), used.end());
    } else {
        n = rnd.next(3, 14);
        k = rnd.next(1, n);
        int chosenRows = rnd.next(1, min(n, 5));
        int chosenCols = rnd.next(1, min(n, 5));
        for (int x = 1; x <= chosenRows; ++x) {
            for (int y = 1; y <= chosenCols; ++y) {
                if (rnd.next(0, 99) < 70) add(x, y);
            }
        }
        if (points.empty()) add(1, 1);
    }

    sort(points.begin(), points.end());
    points.erase(unique(points.begin(), points.end()), points.end());
    shuffle(points.begin(), points.end());

    println(n, (int)points.size(), k);
    for (auto [x, y] : points) {
        println(x, y);
    }

    return 0;
}
