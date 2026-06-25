#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

struct Cell {
    int r;
    int c;
    long long score;
    int tie;
};

vector<vector<int>> assignByScore(int h, int w, vector<Cell> cells) {
    sort(cells.begin(), cells.end(), [](const Cell& a, const Cell& b) {
        return tie(a.score, a.tie) < tie(b.score, b.tie);
    });

    vector<vector<int>> a(h, vector<int>(w));
    for (int i = 0; i < (int)cells.size(); ++i) {
        a[cells[i].r][cells[i].c] = i + 1;
    }
    return a;
}

vector<vector<int>> randomPermutation(int h, int w) {
    vector<int> values(h * w);
    iota(values.begin(), values.end(), 1);
    shuffle(values.begin(), values.end());

    vector<vector<int>> a(h, vector<int>(w));
    int at = 0;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            a[i][j] = values[at++];
        }
    }
    return a;
}

vector<vector<int>> monotoneTerrain(int h, int w) {
    vector<Cell> cells;
    int direction = rnd.next(0, 3);
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            int r = (direction & 1) ? h - 1 - i : i;
            int c = (direction & 2) ? w - 1 - j : j;
            long long score = (long long)r * w + c;
            if (rnd.next(0, 1)) {
                score = (long long)c * h + r;
            }
            cells.push_back({i, j, score, rnd.next(0, 1000000000)});
        }
    }
    return assignByScore(h, w, cells);
}

vector<vector<int>> snakeTerrain(int h, int w) {
    vector<Cell> cells;
    bool vertical = rnd.next(0, 1);
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            int score;
            if (vertical) {
                score = j * h + ((j % 2 == 0) ? i : h - 1 - i);
            } else {
                score = i * w + ((i % 2 == 0) ? j : w - 1 - j);
            }
            cells.push_back({i, j, score, rnd.next(0, 1000000000)});
        }
    }
    return assignByScore(h, w, cells);
}

vector<vector<int>> basinTerrain(int h, int w) {
    int basinCount = rnd.next(2, min(4, h * w));
    vector<pair<int, int>> basins;
    while ((int)basins.size() < basinCount) {
        pair<int, int> p = {rnd.next(0, h - 1), rnd.next(0, w - 1)};
        if (find(basins.begin(), basins.end(), p) == basins.end()) {
            basins.push_back(p);
        }
    }

    vector<Cell> cells;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            int nearest = h + w;
            int second = h + w;
            for (auto [br, bc] : basins) {
                int dist = abs(i - br) + abs(j - bc);
                if (dist < nearest) {
                    second = nearest;
                    nearest = dist;
                } else if (dist < second) {
                    second = dist;
                }
            }
            long long ridgeBonus = second - nearest;
            long long score = (long long)nearest * 100 - ridgeBonus * 9;
            cells.push_back({i, j, score, rnd.next(0, 1000000000)});
        }
    }
    return assignByScore(h, w, cells);
}

vector<vector<int>> ringTerrain(int h, int w) {
    vector<Cell> cells;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            int border = min(min(i, h - 1 - i), min(j, w - 1 - j));
            int centerPull = abs(2 * i - (h - 1)) + abs(2 * j - (w - 1));
            long long score = (long long)border * 1000 - centerPull;
            if (rnd.next(0, 1)) {
                score = -score;
            }
            cells.push_back({i, j, score, rnd.next(0, 1000000000)});
        }
    }
    return assignByScore(h, w, cells);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int h = rnd.next(1, 8);
    int w = rnd.next(1, 8);

    if (mode >= 2 && h * w == 1) {
        h = rnd.next(2, 6);
        w = rnd.next(2, 6);
    }
    if (rnd.next(0, 5) == 0) {
        h = rnd.next(1, 3);
        w = rnd.next(9, 15);
    } else if (rnd.next(0, 5) == 0) {
        h = rnd.next(9, 15);
        w = rnd.next(1, 3);
    }

    vector<vector<int>> a;
    if (mode == 0) {
        a = randomPermutation(h, w);
    } else if (mode == 1) {
        a = monotoneTerrain(h, w);
    } else if (mode == 2) {
        a = snakeTerrain(h, w);
    } else if (mode == 3) {
        a = basinTerrain(h, w);
    } else {
        a = ringTerrain(h, w);
    }

    println(h, w);
    for (int i = 0; i < h; ++i) {
        println(a[i]);
    }

    return 0;
}
