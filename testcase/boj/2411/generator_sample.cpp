#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

using Cell = pair<int, int>;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, mode == 1 ? 100 : 12);
    int m = rnd.next(1, mode == 1 ? 100 : 12);

    vector<Cell> cells;
    cells.reserve(n * m);
    for (int x = 1; x <= n; ++x) {
        for (int y = 1; y <= m; ++y) {
            cells.push_back({x, y});
        }
    }
    shuffle(cells.begin(), cells.end());

    set<Cell> used;
    vector<Cell> items;
    vector<Cell> obstacles;

    auto addItem = [&](Cell c) {
        if (used.insert(c).second) {
            items.push_back(c);
        }
    };

    auto addObstacle = [&](Cell c) {
        if (c == Cell{1, 1} || c == Cell{n, m}) {
            return;
        }
        if (used.insert(c).second) {
            obstacles.push_back(c);
        }
    };

    if (mode == 0) {
        addItem(cells[0]);
    } else if (mode == 1) {
        addItem({rnd.next(1, n), rnd.next(1, m)});
        int targetObstacles = rnd.next(0, min<int>(80, n * m - 1));
        for (Cell c : cells) {
            if ((int)obstacles.size() == targetObstacles) {
                break;
            }
            addObstacle(c);
        }
    } else {
        int chainLen = rnd.next(1, min(8, n + m - 1));
        int x = 1;
        int y = 1;
        for (int i = 0; i < chainLen; ++i) {
            if (rnd.next(0, 3) == 0) {
                addItem({x, y});
            }
            int dxLimit = n - x;
            int dyLimit = m - y;
            if (dxLimit + dyLimit == 0) {
                addItem({x, y});
                break;
            }
            if (dyLimit == 0 || (dxLimit > 0 && rnd.next(0, 1) == 0)) {
                x += rnd.next(1, min(3, dxLimit));
            } else {
                y += rnd.next(1, min(3, dyLimit));
            }
            addItem({x, y});
        }

        int remainingCells = n * m - (int)used.size();
        int extraItems = remainingCells == 0 ? 0 : rnd.next(0, min(5, remainingCells));
        if (mode >= 4 && remainingCells > 0) {
            extraItems = rnd.next(1, min(8, remainingCells));
        }
        for (Cell c : cells) {
            if ((int)items.size() >= chainLen + extraItems) {
                break;
            }
            addItem(c);
        }

        int targetObstacles = rnd.next(0, min(18, n * m - (int)used.size()));
        if (mode == 5 && n > 1 && m > 1) {
            addObstacle({2, 1});
            addObstacle({1, 2});
        }
        targetObstacles += obstacles.size();
        for (Cell c : cells) {
            if ((int)obstacles.size() == targetObstacles) {
                break;
            }
            addObstacle(c);
        }
    }

    if (items.empty()) {
        addItem(cells[0]);
    }

    shuffle(items.begin(), items.end());
    shuffle(obstacles.begin(), obstacles.end());

    println(n, m, (int)items.size(), (int)obstacles.size());
    for (Cell c : items) {
        println(c.first, c.second);
    }
    for (Cell c : obstacles) {
        println(c.first, c.second);
    }

    return 0;
}
