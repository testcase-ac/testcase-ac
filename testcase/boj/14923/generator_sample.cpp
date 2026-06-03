#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 12);
    int m = rnd.next(2, 12);
    vector<vector<int>> maze(n, vector<int>(m, 0));

    pair<int, int> start = {rnd.next(n), rnd.next(m)};
    pair<int, int> finish = start;
    while (finish == start) {
        finish = {rnd.next(n), rnd.next(m)};
    }

    if (mode == 0) {
        int wallPercent = rnd.next(0, 65);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                maze[i][j] = rnd.next(0, 99) < wallPercent;
            }
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                maze[i][j] = 1;
            }
        }

        vector<pair<int, int>> path;
        int x = start.first;
        int y = start.second;
        path.push_back({x, y});
        while (x != finish.first) {
            x += (finish.first > x ? 1 : -1);
            path.push_back({x, y});
        }
        while (y != finish.second) {
            y += (finish.second > y ? 1 : -1);
            path.push_back({x, y});
        }
        for (auto [r, c] : path) {
            maze[r][c] = 0;
        }
        if (path.size() > 2) {
            auto breakCell = path[rnd.next(1, static_cast<int>(path.size()) - 2)];
            maze[breakCell.first][breakCell.second] = 1;
        }
        int extraOpen = rnd.next(0, n * m / 4);
        for (int t = 0; t < extraOpen; ++t) {
            maze[rnd.next(n)][rnd.next(m)] = 0;
        }
    } else if (mode == 2) {
        int splitHorizontal = rnd.next(0, 1);
        if (splitHorizontal && n > 2) {
            int wallRow = rnd.next(1, n - 2);
            for (int j = 0; j < m; ++j) {
                maze[wallRow][j] = 1;
            }
            if (rnd.next(0, 1)) {
                maze[wallRow][rnd.next(m)] = 0;
            }
        } else if (m > 2) {
            int wallCol = rnd.next(1, m - 2);
            for (int i = 0; i < n; ++i) {
                maze[i][wallCol] = 1;
            }
            if (rnd.next(0, 1)) {
                maze[rnd.next(n)][wallCol] = 0;
            }
        }
        int noise = rnd.next(0, n * m / 5);
        for (int t = 0; t < noise; ++t) {
            maze[rnd.next(n)][rnd.next(m)] ^= 1;
        }
    } else if (mode == 3) {
        int wallPercent = rnd.next(70, 95);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                maze[i][j] = rnd.next(0, 99) < wallPercent;
            }
        }
    } else {
        n = rnd.next(2, 5);
        m = rnd.next(2, 5);
        maze.assign(n, vector<int>(m, 0));
        start = {rnd.next(n), rnd.next(m)};
        finish = start;
        while (finish == start) {
            finish = {rnd.next(n), rnd.next(m)};
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                maze[i][j] = rnd.next(0, 1);
            }
        }
    }

    if (rnd.next(0, 9) < 7) {
        maze[start.first][start.second] = 0;
        maze[finish.first][finish.second] = 0;
    } else {
        maze[start.first][start.second] = rnd.next(0, 1);
        maze[finish.first][finish.second] = rnd.next(0, 1);
    }

    println(n, m);
    println(start.first + 1, start.second + 1);
    println(finish.first + 1, finish.second + 1);
    for (int i = 0; i < n; ++i) {
        println(maze[i]);
    }

    return 0;
}
