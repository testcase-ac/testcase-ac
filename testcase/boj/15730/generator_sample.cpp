#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = 0;
    int m = 0;
    vector<vector<int>> h;

    if (mode == 0) {
        n = rnd.next(1, 2);
        m = rnd.next(1, 12);
        h.assign(n, vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                h[i][j] = rnd.next(0, 10000);
            }
        }
    } else if (mode == 1) {
        n = rnd.next(3, 8);
        m = rnd.next(3, 8);
        int wall = rnd.next(5, 30);
        int floor = rnd.next(0, wall - 1);
        h.assign(n, vector<int>(m, floor));
        for (int i = 0; i < n; ++i) {
            h[i][0] = h[i][m - 1] = wall;
        }
        for (int j = 0; j < m; ++j) {
            h[0][j] = h[n - 1][j] = wall;
        }
        int bumps = rnd.next(0, (n - 2) * (m - 2));
        for (int k = 0; k < bumps; ++k) {
            int i = rnd.next(1, n - 2);
            int j = rnd.next(1, m - 2);
            h[i][j] = rnd.next(floor, wall + rnd.next(0, 5));
        }
    } else if (mode == 2) {
        n = rnd.next(4, 9);
        m = rnd.next(4, 9);
        int wall = rnd.next(6, 50);
        int floor = rnd.next(0, wall - 2);
        h.assign(n, vector<int>(m, floor));
        for (int i = 0; i < n; ++i) {
            h[i][0] = h[i][m - 1] = wall;
        }
        for (int j = 0; j < m; ++j) {
            h[0][j] = h[n - 1][j] = wall;
        }
        if (rnd.next(0, 1) == 0) {
            h[rnd.next(0, n - 1)][rnd.next(0, 1) * (m - 1)] = rnd.next(0, wall - 1);
        } else {
            h[rnd.next(0, 1) * (n - 1)][rnd.next(0, m - 1)] = rnd.next(0, wall - 1);
        }
    } else if (mode == 3) {
        n = rnd.next(5, 10);
        m = rnd.next(5, 10);
        h.assign(n, vector<int>(m));
        int base = rnd.next(0, 20);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                h[i][j] = base + min({i, j, n - 1 - i, m - 1 - j}) * rnd.next(1, 4);
            }
        }
    } else if (mode == 4) {
        n = rnd.next(3, 10);
        m = rnd.next(3, 10);
        h.assign(n, vector<int>(m));
        for (int i = 0; i < n; ++i) {
            int row = rnd.next(0, 40);
            for (int j = 0; j < m; ++j) {
                h[i][j] = row + rnd.next(0, 3);
            }
        }
    } else if (mode == 5) {
        n = rnd.next(3, 10);
        m = rnd.next(3, 10);
        h.assign(n, vector<int>(m));
        for (int j = 0; j < m; ++j) {
            int col = rnd.next(0, 40);
            for (int i = 0; i < n; ++i) {
                h[i][j] = col + rnd.next(0, 3);
            }
        }
    } else if (mode == 6) {
        n = rnd.next(8, 15);
        m = rnd.next(8, 15);
        h.assign(n, vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                h[i][j] = rnd.next(0, 12);
            }
        }
    } else {
        n = rnd.next(3, 7);
        m = rnd.next(3, 7);
        int a = rnd.next(0, 10000);
        int b = rnd.next(0, 10000);
        h.assign(n, vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                h[i][j] = rnd.next(0, 1) == 0 ? a : b;
            }
        }
    }

    println(n, m);
    for (int i = 0; i < n; ++i) {
        println(h[i]);
    }

    return 0;
}
