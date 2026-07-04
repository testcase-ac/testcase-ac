#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct Couch {
    int r;
    int c;
    bool horizontal;
    bool upper;
};

char labelFor(int index, bool upper) {
    char base = upper ? 'A' : 'a';
    return char(base + (index % 26));
}

bool canPlace(const vector<string>& grid, int r, int c, bool horizontal) {
    int n = (int)grid.size();
    int m = (int)grid[0].size();
    int r2 = r + (horizontal ? 0 : 1);
    int c2 = c + (horizontal ? 1 : 0);
    return 0 <= r && r2 < n && 0 <= c && c2 < m && grid[r][c] == '.' && grid[r2][c2] == '.';
}

void place(vector<string>& grid, const Couch& couch, int index) {
    char ch = labelFor(index, couch.upper);
    grid[couch.r][couch.c] = ch;
    grid[couch.r + (couch.horizontal ? 0 : 1)][couch.c + (couch.horizontal ? 1 : 0)] = ch;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n;
    int m;

    if (mode == 0) {
        n = rnd.next(1, 2);
        m = rnd.next(1, 3);
    } else if (mode == 1) {
        n = rnd.next(2, 4);
        m = rnd.next(2, 4);
    } else if (mode == 2) {
        n = rnd.next(3, 6);
        m = rnd.next(3, 7);
    } else if (mode == 3) {
        n = rnd.next(1, 5);
        m = rnd.next(6, 12);
    } else {
        n = rnd.next(6, 12);
        m = rnd.next(1, 5);
    }

    vector<string> grid(n, string(m, '.'));
    vector<Couch> candidates;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (c + 1 < m) {
                candidates.push_back({r, c, true, rnd.next(2) == 0});
            }
            if (r + 1 < n) {
                candidates.push_back({r, c, false, rnd.next(2) == 0});
            }
        }
    }

    shuffle(candidates.begin(), candidates.end());

    int maxCouches = min(26, (n * m) / 2);
    int target = maxCouches == 0 ? 0 : rnd.next(0, maxCouches);
    if (mode != 0 && maxCouches > 0) {
        target = max(1, target);
    }

    int placed = 0;
    for (const Couch& couch : candidates) {
        if (placed >= target) {
            break;
        }
        if (!canPlace(grid, couch.r, couch.c, couch.horizontal)) {
            continue;
        }

        if (mode == 2 && rnd.next(100) < 35) {
            continue;
        }

        place(grid, couch, placed);
        ++placed;
    }

    println(n, m);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
