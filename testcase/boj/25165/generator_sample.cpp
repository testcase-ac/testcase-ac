#include "testlib.h"
#include <utility>
#include <vector>

using namespace std;

static vector<pair<int, int>> visitedCells(int n, int m, int ac, int d) {
    vector<pair<int, int>> cells;
    int r = 1;
    int c = ac;

    while (true) {
        cells.emplace_back(r, c);
        if (r == n && c == m) break;

        if (d == 1) {
            if (c == m) {
                ++r;
                d ^= 1;
            } else {
                ++c;
            }
        } else {
            if (c == 1) {
                ++r;
                d ^= 1;
            } else {
                --c;
            }
        }
    }

    return cells;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;
    if (mode == 0) {
        n = rnd.next(2, 6);
        m = rnd.next(2, 6);
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        m = rnd.next(2, 12);
    } else if (mode == 2) {
        n = rnd.next(80, 100);
        m = rnd.next(80, 100);
    } else if (mode == 3) {
        n = rnd.any(vector<int>{2, 3, 100});
        m = rnd.next(2, 100);
    } else if (mode == 4) {
        n = rnd.next(2, 100);
        m = rnd.any(vector<int>{2, 3, 100});
    } else {
        n = rnd.next(2, 100);
        m = rnd.next(2, 100);
    }

    int ac;
    if (rnd.next(0, 4) == 0) {
        ac = rnd.any(vector<int>{1, m});
    } else {
        ac = rnd.next(1, m);
    }
    int d = rnd.next(0, 1);

    vector<pair<int, int>> path;
    vector<pair<int, int>> offPath;
    vector<vector<bool>> seen(n + 1, vector<bool>(m + 1, false));
    for (auto cell : visitedCells(n, m, ac, d)) {
        seen[cell.first][cell.second] = true;
        if (cell.first >= 2 && !(cell.first == n && cell.second == m)) {
            path.push_back(cell);
        }
    }

    for (int r = 2; r <= n; ++r) {
        for (int c = 1; c <= m; ++c) {
            if (r == n && c == m) continue;
            if (!seen[r][c]) offPath.emplace_back(r, c);
        }
    }

    pair<int, int> monster;
    bool preferPath = rnd.next(0, 1) == 1;
    if (!path.empty() && (preferPath || offPath.empty())) {
        monster = rnd.any(path);
    } else {
        monster = rnd.any(offPath);
    }

    println(n, m);
    println(ac, d);
    println(monster.first, monster.second);

    return 0;
}
