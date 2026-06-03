#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

using Cell = pair<int, int>;

static void addSegment(vector<Cell>& path, int& r, int& c, int tr, int tc) {
    while (r != tr) {
        r += (tr > r ? 1 : -1);
        path.push_back({r, c});
    }
    while (c != tc) {
        c += (tc > c ? 1 : -1);
        path.push_back({r, c});
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int n = rnd.next(2, mode == 3 ? 30 : 16);

    vector<string> grid(n, string(n, '.'));
    vector<vector<int>> onPath(n, vector<int>(n, 0));

    int ar = rnd.next(n);
    int ac = rnd.next(n);
    int br = rnd.next(n);
    int bc = rnd.next(n);
    while (ar == br && ac == bc) {
        br = rnd.next(n);
        bc = rnd.next(n);
    }

    if (mode == 0) {
        if (rnd.next(2) == 0) {
            br = ar;
            while (bc == ac) {
                bc = rnd.next(n);
            }
        } else {
            bc = ac;
            while (br == ar) {
                br = rnd.next(n);
            }
        }
    }

    vector<Cell> path;
    int r = ar;
    int c = ac;
    path.push_back({r, c});

    if (mode == 1) {
        addSegment(path, r, c, br, c);
        addSegment(path, r, c, br, bc);
    } else if (mode == 2 || mode == 3) {
        int bends = rnd.next(mode == 2 ? 1 : 2, mode == 2 ? 3 : 6);
        for (int i = 0; i < bends; ++i) {
            if (rnd.next(2) == 0) {
                addSegment(path, r, c, rnd.next(n), c);
            } else {
                addSegment(path, r, c, r, rnd.next(n));
            }
        }
        addSegment(path, r, c, br, c);
        addSegment(path, r, c, br, bc);
    } else {
        addSegment(path, r, c, br, bc);
    }

    for (Cell cell : path) {
        onPath[cell.first][cell.second] = 1;
    }

    int obstaclePercent = 0;
    if (mode == 1) {
        obstaclePercent = rnd.next(5, 25);
    } else if (mode == 2) {
        obstaclePercent = rnd.next(20, 45);
    } else if (mode == 3) {
        obstaclePercent = rnd.next(35, 65);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!onPath[i][j] && rnd.next(100) < obstaclePercent) {
                grid[i][j] = 'x';
            }
        }
    }

    grid[ar][ac] = 'A';
    grid[br][bc] = 'B';

    println(n);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
