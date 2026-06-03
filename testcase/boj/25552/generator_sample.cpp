#include "testlib.h"
#include <algorithm>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

using Grid = vector<string>;

Grid makeGrid(int n, int m, char fill) {
    return Grid(n, string(m, fill));
}

vector<pair<int, int>> cellsWithin(int n, int m, int r, int c, int d) {
    vector<pair<int, int>> cells;
    for (int nr = max(0, r - d); nr <= min(n - 1, r + d); ++nr) {
        int rem = d - abs(nr - r);
        for (int nc = max(0, c - rem); nc <= min(m - 1, c + rem); ++nc) {
            cells.push_back({nr, nc});
        }
    }
    return cells;
}

Grid randomGrid(int n, int m, int percentO) {
    Grid grid = makeGrid(n, m, 'X');
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (rnd.next(100) < percentO) {
                grid[r][c] = 'O';
            }
        }
    }
    return grid;
}

Grid reachableSubset(const Grid& initial, int d, int growPercent) {
    int n = (int)initial.size();
    int m = (int)initial[0].size();
    Grid predicted = initial;
    queue<pair<int, int>> q;

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (initial[r][c] == 'O') {
                q.push({r, c});
            }
        }
    }

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        vector<pair<int, int>> around = cellsWithin(n, m, r, c, d);
        shuffle(around.begin(), around.end());
        for (auto [nr, nc] : around) {
            if (predicted[nr][nc] == 'O' || rnd.next(100) >= growPercent) {
                continue;
            }
            predicted[nr][nc] = 'O';
            q.push({nr, nc});
        }
    }

    return predicted;
}

void printCase(const Grid& initial, int d, const Grid& predicted) {
    println((int)initial.size(), (int)initial[0].size());
    for (const string& row : initial) {
        println(row);
    }
    println(d);
    for (const string& row : predicted) {
        println(row);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(1, 14);
    int m = rnd.next(1, 14);
    int d = rnd.next(1, 8);
    Grid initial;
    Grid predicted;

    if (mode == 0) {
        n = rnd.next(1, 4);
        m = rnd.next(1, 8);
        initial = makeGrid(n, m, 'X');
        predicted = randomGrid(n, m, rnd.next(0, 45));
    } else if (mode == 1) {
        initial = randomGrid(n, m, rnd.next(25, 80));
        predicted = initial;
        vector<pair<int, int>> grass;
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                if (initial[r][c] == 'O') {
                    grass.push_back({r, c});
                }
            }
        }
        if (grass.empty()) {
            int r = rnd.next(n);
            int c = rnd.next(m);
            initial[r][c] = predicted[r][c] = 'O';
            grass.push_back({r, c});
        }
        shuffle(grass.begin(), grass.end());
        int removeCount = rnd.next(1, (int)grass.size());
        for (int i = 0; i < removeCount; ++i) {
            predicted[grass[i].first][grass[i].second] = 'X';
        }
    } else if (mode == 2) {
        initial = randomGrid(n, m, rnd.next(5, 30));
        predicted = reachableSubset(initial, d, rnd.next(5, 45));
    } else if (mode == 3) {
        n = rnd.next(3, 15);
        m = rnd.next(3, 15);
        initial = makeGrid(n, m, 'X');
        predicted = makeGrid(n, m, 'X');
        int r = rnd.next(n);
        int c = rnd.next(m);
        initial[r][c] = predicted[r][c] = 'O';
        int farR = (r < n / 2 ? n - 1 : 0);
        int farC = (c < m / 2 ? m - 1 : 0);
        predicted[farR][farC] = 'O';
    } else if (mode == 4) {
        n = rnd.next(2, 12);
        m = rnd.next(2, 12);
        d = rnd.any(vector<int>{1, 8});
        initial = makeGrid(n, m, 'X');
        predicted = makeGrid(n, m, 'X');
        int parity = rnd.next(2);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                if ((r + c) % 2 == parity) {
                    initial[r][c] = 'O';
                }
                if (r == 0 || c == 0 || r == n - 1 || c == m - 1 || rnd.next(100) < 20) {
                    predicted[r][c] = 'O';
                }
            }
        }
    } else {
        n = rnd.next(12, 25);
        m = rnd.next(12, 25);
        d = rnd.next(1, 8);
        initial = randomGrid(n, m, rnd.next(1, 20));
        predicted = randomGrid(n, m, rnd.next(20, 70));
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                if (initial[r][c] == 'O' && rnd.next(100) < 80) {
                    predicted[r][c] = 'O';
                }
            }
        }
    }

    printCase(initial, d, predicted);
    return 0;
}
