#include "testlib.h"

#include <algorithm>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int>> shuffledNeighbors(int i, int j) {
    vector<pair<int, int>> next = {{i - 1, j}, {i + 1, j}, {i, j - 1}, {i, j + 1}};
    shuffle(next.begin(), next.end());
    return next;
}

bool reachable(const vector<string>& grid, pair<int, int> start, pair<int, int> finish) {
    int h = int(grid.size());
    int w = int(grid[0].size());
    vector<vector<int>> seen(h, vector<int>(w));
    queue<pair<int, int>> q;
    seen[start.first][start.second] = 1;
    q.push(start);

    while (!q.empty()) {
        auto [i, j] = q.front();
        q.pop();
        if (make_pair(i, j) == finish) {
            return true;
        }

        for (auto [ni, nj] : shuffledNeighbors(i, j)) {
            if (ni < 0 || ni >= h || nj < 0 || nj >= w) {
                continue;
            }
            if (seen[ni][nj] || grid[ni][nj] == '#') {
                continue;
            }
            seen[ni][nj] = 1;
            q.push({ni, nj});
        }
    }

    return false;
}

void carveDirectPath(vector<string>& grid, pair<int, int> start, pair<int, int> finish) {
    int i = start.first;
    int j = start.second;
    grid[i][j] = '.';

    bool rowFirst = rnd.next(0, 1);
    while (i != finish.first || j != finish.second) {
        bool moveRow = (rowFirst && i != finish.first) || j == finish.second;
        if (moveRow) {
            i += (finish.first > i ? 1 : -1);
        } else {
            j += (finish.second > j ? 1 : -1);
        }
        grid[i][j] = '.';
        if (rnd.next(0, 4) == 0) {
            rowFirst = !rowFirst;
        }
    }
}

void addSnakeCorridor(vector<string>& grid) {
    int h = int(grid.size());
    int w = int(grid[0].size());
    for (int i = 1; i + 1 < h; ++i) {
        if (i % 2 == 1) {
            for (int j = 1; j + 1 < w; ++j) {
                grid[i][j] = '.';
            }
        } else {
            int opening = (i / 2) % 2 == 0 ? w - 2 : 1;
            grid[i][opening] = '.';
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int h = rnd.next(3, 18);
    int w = rnd.next(3, 18);
    if (h == 3 && w == 3) {
        w = 4;
    }
    vector<string> grid(h, string(w, '#'));

    pair<int, int> start = {rnd.next(1, h - 2), rnd.next(1, w - 2)};
    pair<int, int> finish = start;
    while (finish == start) {
        finish = {rnd.next(1, h - 2), rnd.next(1, w - 2)};
    }

    if (mode == 0) {
        for (int i = 1; i + 1 < h; ++i) {
            for (int j = 1; j + 1 < w; ++j) {
                grid[i][j] = rnd.next(0, 99) < 85 ? '.' : '#';
            }
        }
        carveDirectPath(grid, start, finish);
    } else if (mode == 1) {
        carveDirectPath(grid, start, finish);
        int extra = rnd.next(0, max(1, (h - 2) * (w - 2) / 2));
        for (int k = 0; k < extra; ++k) {
            int i = rnd.next(1, h - 2);
            int j = rnd.next(1, w - 2);
            grid[i][j] = '.';
        }
    } else if (mode == 2) {
        addSnakeCorridor(grid);
        carveDirectPath(grid, start, finish);
    } else {
        for (int i = 1; i + 1 < h; ++i) {
            for (int j = 1; j + 1 < w; ++j) {
                bool nearBorder = i == 1 || i == h - 2 || j == 1 || j == w - 2;
                int openChance = nearBorder ? 95 : 45;
                grid[i][j] = rnd.next(0, 99) < openChance ? '.' : '#';
            }
        }
        carveDirectPath(grid, start, finish);
    }

    if (!reachable(grid, start, finish)) {
        carveDirectPath(grid, start, finish);
    }

    grid[start.first][start.second] = 'S';
    grid[finish.first][finish.second] = 'E';

    println(h, w);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
