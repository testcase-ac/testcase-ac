#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(1, 12);
    int m = rnd.next(1, 12);
    set<pair<int, int>> marked;

    if (mode == 0) {
        if (rnd.next(2) == 0) {
            n = 1;
            m = rnd.next(1, 20);
        } else {
            n = rnd.next(1, 20);
            m = 1;
        }
        int k = rnd.next(1, n * m);
        vector<pair<int, int>> cells;
        for (int x = 1; x <= n; ++x) {
            for (int y = 1; y <= m; ++y) {
                cells.emplace_back(x, y);
            }
        }
        shuffle(cells.begin(), cells.end());
        marked.insert(cells.begin(), cells.begin() + k);
    } else if (mode == 1) {
        n = rnd.next(1, 8);
        m = rnd.next(1, 8);
        for (int x = 1; x <= n; ++x) {
            for (int y = 1; y <= m; ++y) {
                marked.insert({x, y});
            }
        }
    } else if (mode == 2) {
        double density = rnd.next(0.08, 0.45);
        for (int x = 1; x <= n; ++x) {
            for (int y = 1; y <= m; ++y) {
                if (rnd.next() < density) {
                    marked.insert({x, y});
                }
            }
        }
    } else if (mode == 3) {
        n = rnd.next(2, 14);
        m = rnd.next(2, 14);
        vector<int> cols;
        for (int y = 1; y <= m; ++y) {
            cols.push_back(y);
        }
        shuffle(cols.begin(), cols.end());
        int lim = min(n, m);
        for (int x = 1; x <= lim; ++x) {
            marked.insert({x, cols[x - 1]});
            if (rnd.next(3) == 0) {
                marked.insert({x, rnd.next(1, m)});
            }
        }
    } else if (mode == 4) {
        n = rnd.next(4, 16);
        m = rnd.next(4, 16);
        int rowLimit = rnd.next(1, n);
        int colLimit = rnd.next(1, m);
        for (int x = 1; x <= rowLimit; ++x) {
            for (int y = 1; y <= colLimit; ++y) {
                if (rnd.next(4) != 0) {
                    marked.insert({x, y});
                }
            }
        }
        int extras = rnd.next(0, min(10, n * m));
        while (extras--) {
            marked.insert({rnd.next(1, n), rnd.next(1, m)});
        }
    } else {
        n = rnd.next(2, 15);
        m = rnd.next(2, 15);
        bool descending = rnd.next(2);
        for (int x = 1; x <= n; ++x) {
            int limit = descending ? max(1, m - x + 1) : min(m, x);
            for (int y = 1; y <= limit; ++y) {
                if (rnd.next(3) != 0) {
                    marked.insert({x, y});
                }
            }
        }
    }

    if (marked.empty()) {
        marked.insert({rnd.next(1, n), rnd.next(1, m)});
    }

    vector<pair<int, int>> cells(marked.begin(), marked.end());
    shuffle(cells.begin(), cells.end());

    println(n, m, int(cells.size()));
    for (auto [x, y] : cells) {
        println(x, y);
    }

    return 0;
}
