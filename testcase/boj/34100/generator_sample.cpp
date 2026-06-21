#include "testlib.h"
#include <string>
#include <vector>

using namespace std;

using Grid = vector<string>;

Grid makeBlocked(int n, int m) {
    return Grid(n, string(m, '#'));
}

Grid makeRandomGrid(int n, int m) {
    int dotPercent = rnd.next(15, 85);
    Grid g(n, string(m, '#'));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            g[i][j] = (rnd.next(100) < dotPercent ? '.' : '#');
        }
    }
    return g;
}

Grid makeStripedGrid(int n, int m) {
    Grid g(n, string(m, '#'));
    int mode = rnd.next(4);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (mode == 0) g[i][j] = (i % 2 == 0 ? '.' : '#');
            if (mode == 1) g[i][j] = (j % 2 == 0 ? '.' : '#');
            if (mode == 2) g[i][j] = ((i + j) % 2 == 0 ? '.' : '#');
            if (mode == 3) g[i][j] = ((i + 2 * j) % 3 == 0 ? '#' : '.');
        }
    }
    return g;
}

Grid makePlacedBlocksGrid(int n, int m) {
    Grid g(n, string(m, '#'));
    vector<pair<int, int>> anchors;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j + 1 < m; ++j) {
            anchors.push_back({i, j});
        }
    }
    shuffle(anchors.begin(), anchors.end());

    for (auto [r, c] : anchors) {
        if (rnd.next(100) >= 45) continue;

        bool rightBlock = rnd.next(2);
        vector<pair<int, int>> cells;
        if (rightBlock) {
            cells = {{r, c}, {r - 1, c + 1}, {r, c + 1}};
        } else {
            cells = {{r, c}, {r - 1, c}, {r, c + 1}};
        }

        bool free = true;
        for (auto [x, y] : cells) {
            if (g[x][y] == '.') free = false;
        }
        if (!free) continue;

        for (auto [x, y] : cells) {
            g[x][y] = '.';
        }
    }

    return g;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(4, 12);
    vector<Grid> cases;

    for (int tc = 0; tc < t; ++tc) {
        int n = rnd.next(2, 10);
        int m = rnd.next(2, 12);
        int mode = rnd.next(6);

        if (mode == 0) {
            cases.push_back(makeBlocked(n, m));
        } else if (mode == 1) {
            cases.push_back(Grid(n, string(m, '.')));
        } else if (mode == 2) {
            cases.push_back(makeStripedGrid(n, m));
        } else if (mode == 3) {
            cases.push_back(makePlacedBlocksGrid(n, m));
        } else {
            cases.push_back(makeRandomGrid(n, m));
        }
    }

    println(t);
    for (const Grid& g : cases) {
        println(static_cast<int>(g.size()), static_cast<int>(g[0].size()));
        for (const string& row : g) {
            println(row);
        }
    }

    return 0;
}
