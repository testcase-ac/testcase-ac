#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

using Cell = pair<int, int>;

bool covers(int top, int left, int height, int width, int r, int c) {
    return top <= r && r < top + height && left <= c && c < left + width;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 12);
    int m = rnd.next(2, 12);
    int a = rnd.next(1, min(5, n));
    int b = rnd.next(1, min(5, m));

    if (n - a + 1 == 1 && m - b + 1 == 1) {
        if (n < 12) {
            ++n;
        } else {
            ++m;
        }
    }

    vector<Cell> positions;
    for (int r = 1; r <= n - a + 1; ++r) {
        for (int c = 1; c <= m - b + 1; ++c) {
            positions.push_back({r, c});
        }
    }
    shuffle(positions.begin(), positions.end());
    Cell start = positions[0];
    Cell finish = positions[1];

    set<Cell> obstacles;
    auto canBlock = [&](int r, int c) {
        if (obstacles.count({r, c})) {
            return false;
        }
        if (covers(start.first, start.second, a, b, r, c)) {
            return false;
        }
        if (covers(finish.first, finish.second, a, b, r, c)) {
            return false;
        }
        return true;
    };
    auto addObstacle = [&](int r, int c) {
        if (canBlock(r, c)) {
            obstacles.insert({r, c});
        }
    };

    if (mode == 1) {
        int tries = rnd.next(1, n * m / 3 + 1);
        for (int i = 0; i < tries; ++i) {
            addObstacle(rnd.next(1, n), rnd.next(1, m));
        }
    } else if (mode == 2) {
        int wallCol = rnd.next(1, m);
        int gap = rnd.next(1, n);
        for (int r = 1; r <= n; ++r) {
            if (r != gap) {
                addObstacle(r, wallCol);
            }
        }
    } else if (mode == 3) {
        int wallRow = rnd.next(1, n);
        int gap = rnd.next(1, m);
        for (int c = 1; c <= m; ++c) {
            if (c != gap) {
                addObstacle(wallRow, c);
            }
        }
    } else if (mode == 4) {
        for (int d = 0; d < 4; ++d) {
            int nr = finish.first + (d == 0) - (d == 1);
            int nc = finish.second + (d == 2) - (d == 3);
            if (1 <= nr && nr <= n && 1 <= nc && nc <= m) {
                addObstacle(nr, nc);
            }
        }
    } else if (mode == 5) {
        int tries = rnd.next(n * m / 4, n * m / 2);
        for (int i = 0; i < tries; ++i) {
            addObstacle(rnd.next(1, n), rnd.next(1, m));
        }
    }

    vector<Cell> obstacleList(obstacles.begin(), obstacles.end());
    shuffle(obstacleList.begin(), obstacleList.end());

    println(n, m, a, b, static_cast<int>(obstacleList.size()));
    for (Cell cell : obstacleList) {
        println(cell.first, cell.second);
    }
    println(start.first, start.second);
    println(finish.first, finish.second);

    return 0;
}
