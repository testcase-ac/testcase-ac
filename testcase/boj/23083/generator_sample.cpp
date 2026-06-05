#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Cell = pair<int, int>;

static void addHole(set<Cell>& holes, int n, int m, int x, int y) {
    if (x < 1 || x > n || y < 1 || y > m) return;
    if (x == 1 && y == 1) return;
    if (x == n && y == m) return;
    holes.emplace(x, y);
}

static void addRandomHoles(set<Cell>& holes, int n, int m, int target) {
    vector<Cell> cells;
    cells.reserve(n * m);
    for (int x = 1; x <= n; ++x) {
        for (int y = 1; y <= m; ++y) {
            if ((x == 1 && y == 1) || (x == n && y == m)) continue;
            cells.emplace_back(x, y);
        }
    }

    shuffle(cells.begin(), cells.end());
    target = min(target, static_cast<int>(cells.size()));
    for (int i = 0; i < target; ++i) {
        holes.insert(cells[i]);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n, m;
    set<Cell> holes;

    if (mode == 0) {
        n = rnd.next(2, 8);
        m = rnd.next(2, 8);
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        m = rnd.next(2, 12);
        addRandomHoles(holes, n, m, rnd.next(1, min(n * m - 2, 12)));
    } else if (mode == 2) {
        n = rnd.next(4, 14);
        m = rnd.next(4, 14);
        int col = rnd.next(2, m - 1);
        for (int x = 1; x <= n; ++x) {
            if (rnd.next(0, 4) != 0) addHole(holes, n, m, x, col);
        }
        addRandomHoles(holes, n, m, rnd.next(0, min(n * m - 2, 8)));
    } else if (mode == 3) {
        n = rnd.next(4, 14);
        m = rnd.next(4, 14);
        int row = rnd.next(2, n - 1);
        for (int y = 1; y <= m; ++y) {
            if (rnd.next(0, 3) != 0) addHole(holes, n, m, row, y);
        }
        addRandomHoles(holes, n, m, rnd.next(0, min(n * m - 2, 8)));
    } else if (mode == 4) {
        n = rnd.next(2, 20);
        m = rnd.next(2, 20);
        int edgeBudget = rnd.next(1, min(20, n * m - 2));
        for (int i = 0; i < edgeBudget; ++i) {
            int side = rnd.next(0, 3);
            if (side == 0) addHole(holes, n, m, 1, rnd.next(1, m));
            if (side == 1) addHole(holes, n, m, n, rnd.next(1, m));
            if (side == 2) addHole(holes, n, m, rnd.next(1, n), 1);
            if (side == 3) addHole(holes, n, m, rnd.next(1, n), m);
        }
        addRandomHoles(holes, n, m, rnd.next(0, min(n * m - 2, 6)));
    } else if (mode == 5) {
        n = rnd.next(20, 60);
        m = rnd.next(20, 60);
        addRandomHoles(holes, n, m, rnd.next(20, 120));
    } else if (mode == 6) {
        n = rnd.next(2, 1000);
        m = rnd.next(2, 1000);
        int limit = min(n * m - 2, 10000);
        addRandomHoles(holes, n, m, rnd.next(0, min(limit, 180)));
    } else {
        n = rnd.any(vector<int>{2, 3, 999, 1000});
        m = rnd.any(vector<int>{2, 3, 999, 1000});
        int limit = min(n * m - 2, 10000);
        addRandomHoles(holes, n, m, rnd.next(0, min(limit, 220)));
    }

    vector<Cell> out(holes.begin(), holes.end());
    shuffle(out.begin(), out.end());

    println(n, m);
    println(static_cast<int>(out.size()));
    for (Cell cell : out) {
        println(cell.first, cell.second);
    }

    return 0;
}
