#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

struct Obstacle {
    int x;
    int y;
    int h;
};

static vector<pair<int, int>> candidateCells(int h, int w, pair<int, int> start, pair<int, int> finish) {
    vector<pair<int, int>> cells;
    for (int x = 1; x <= h; ++x) {
        for (int y = 1; y <= w; ++y) {
            pair<int, int> cell = {x, y};
            if (cell != start && cell != finish) {
                cells.push_back(cell);
            }
        }
    }
    shuffle(cells.begin(), cells.end());
    return cells;
}

static vector<Obstacle> makeObstacles(int h, int w, pair<int, int> start, pair<int, int> finish, int mode) {
    vector<pair<int, int>> cells = candidateCells(h, w, start, finish);
    int maxCells = (int)cells.size();

    int count = 0;
    if (mode == 0) {
        count = 0;
    } else if (mode == 1) {
        count = rnd.next(0, min(maxCells, max(1, h + w - 2)));
    } else if (mode == 2) {
        count = rnd.next(maxCells / 3, maxCells);
    } else {
        count = rnd.next(0, min(maxCells, max(2, (h * w) / 2)));
    }

    vector<Obstacle> obstacles;
    obstacles.reserve(count);
    for (int i = 0; i < count; ++i) {
        int height;
        if (mode == 1) {
            height = rnd.next(1, 12);
        } else if (mode == 2) {
            height = rnd.next(35, 50);
        } else {
            height = rnd.next(1, 50);
        }
        obstacles.push_back({cells[i].first, cells[i].second, height});
    }

    sort(obstacles.begin(), obstacles.end(), [](const Obstacle& a, const Obstacle& b) {
        return make_pair(a.x, a.y) < make_pair(b.x, b.y);
    });
    return obstacles;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 10);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 3);
        int h;
        int w;
        if (mode == 0) {
            h = rnd.next(2, 4);
            w = rnd.next(2, 4);
        } else if (mode == 2) {
            h = rnd.next(3, 8);
            w = rnd.next(3, 8);
        } else {
            h = rnd.next(2, 12);
            w = rnd.next(2, 12);
        }

        pair<int, int> start = {rnd.next(1, h), rnd.next(1, w)};
        pair<int, int> finish = {rnd.next(1, h), rnd.next(1, w)};
        if (rnd.next(0, 4) != 0) {
            while (finish == start) {
                finish = {rnd.next(1, h), rnd.next(1, w)};
            }
        }

        int distance = abs(start.first - finish.first) + abs(start.second - finish.second);
        int f;
        if (mode == 0) {
            f = rnd.next(0, max(0, distance + 1));
        } else if (mode == 1) {
            f = rnd.next(max(0, distance - 2), distance + 5);
        } else if (mode == 2) {
            f = rnd.next(0, min(10000, distance + 3));
        } else {
            f = rnd.next(0, 60);
        }

        vector<Obstacle> obstacles = makeObstacles(h, w, start, finish, mode);
        printf("%d %d %d %d %d %d %d %d\n", h, w, (int)obstacles.size(), f, start.first, start.second,
               finish.first, finish.second);
        for (const Obstacle& obstacle : obstacles) {
            println(obstacle.x, obstacle.y, obstacle.h);
        }
    }

    return 0;
}
