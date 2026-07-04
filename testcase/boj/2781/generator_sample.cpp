#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

struct Case {
    int n;
    int m;
    vector<string> grid;
    int sx;
    int sy;
    int dx;
    int dy;
};

static string randomRow(int m, int mode, int row, int n) {
    string s;
    s.reserve(m);

    for (int col = 0; col < m; ++col) {
        int value = 1;
        if (mode == 0) {
            value = rnd.next(1, 9);
        } else if (mode == 1) {
            value = rnd.next(1, 3);
        } else if (mode == 2) {
            value = rnd.next(7, 9);
        } else if (mode == 3) {
            value = (row + col) % 2 == 0 ? rnd.next(1, 3) : rnd.next(7, 9);
        } else {
            int fromStart = row + col;
            int fromEnd = (n - 1 - row) + (m - 1 - col);
            value = fromStart <= fromEnd ? rnd.next(6, 9) : rnd.next(1, 4);
        }
        s.push_back(char('0' + value));
    }

    return s;
}

static Case makeCase(int mode) {
    int n;
    int m;
    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 25);
    } else if (mode == 1) {
        n = rnd.next(1, 25);
        m = 1;
    } else if (mode == 2) {
        n = rnd.next(2, 8);
        m = rnd.next(2, 8);
    } else if (mode == 3) {
        n = rnd.next(8, 18);
        m = rnd.next(8, 18);
    } else {
        n = rnd.next(2, 50);
        m = rnd.next(2, 50);
        while (n * m > 450) {
            if (n >= m) {
                n = rnd.next(2, max(2, n - 1));
            } else {
                m = rnd.next(2, max(2, m - 1));
            }
        }
    }

    int digitMode = rnd.next(0, 4);
    vector<string> grid;
    grid.reserve(n);
    for (int row = 0; row < n; ++row) {
        grid.push_back(randomRow(m, digitMode, row, n));
    }

    int sx = rnd.next(1, n);
    int sy = rnd.next(1, m);
    int dx = rnd.next(1, n);
    int dy = rnd.next(1, m);

    if (mode >= 2 && rnd.next(0, 2) == 0) {
        sx = 1;
        sy = 1;
        dx = n;
        dy = m;
    } else if (rnd.next(0, 5) == 0) {
        dx = sx;
        dy = sy;
    }

    return {n, m, grid, sx, sy, dx, dy};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxTotalCells = 2500;
    int targetCases = rnd.next(3, 8);
    vector<Case> cases;
    cases.reserve(targetCases);

    int totalCells = 0;
    for (int i = 0; i < targetCases; ++i) {
        Case tc = makeCase(rnd.next(0, 4));
        if (totalCells + tc.n * tc.m > maxTotalCells) {
            break;
        }
        totalCells += tc.n * tc.m;
        cases.push_back(tc);
    }

    println((int)cases.size());
    for (const Case& tc : cases) {
        println(tc.n, tc.m);
        for (const string& row : tc.grid) {
            println(row);
        }
        println(tc.sx, tc.sy, tc.dx, tc.dy);
    }

    return 0;
}
