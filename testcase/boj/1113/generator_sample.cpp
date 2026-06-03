#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

using Grid = vector<string>;

void printGrid(const Grid& g) {
    println((int)g.size(), (int)g[0].size());
    for (const string& row : g) {
        println(row);
    }
}

void setRect(Grid& g, int r1, int c1, int r2, int c2, char value) {
    for (int r = r1; r <= r2; ++r) {
        for (int c = c1; c <= c2; ++c) {
            g[r][c] = value;
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    Grid g;

    if (mode == 0) {
        int n = rnd.next(1, 3);
        int m = rnd.next(1, 50);
        if (rnd.next(2)) {
            swap(n, m);
        }
        g.assign(n, string(m, '1'));
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                g[r][c] = char('1' + rnd.next(9));
            }
        }
    } else if (mode == 1) {
        int n = rnd.next(3, 14);
        int m = rnd.next(3, 18);
        int low = rnd.next(1, 5);
        int high = rnd.next(low, 9);
        g.assign(n, string(m, '1'));
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                g[r][c] = char('0' + rnd.next(low, high));
            }
        }
    } else if (mode == 2) {
        int n = rnd.next(3, 15);
        int m = rnd.next(3, 18);
        char wall = char('5' + rnd.next(5));
        char inside = char('1' + rnd.next(wall - '1'));
        g.assign(n, string(m, wall));
        setRect(g, 1, 1, n - 2, m - 2, inside);

        int bumps = rnd.next(0, max(1, (n * m) / 8));
        for (int i = 0; i < bumps; ++i) {
            int r = rnd.next(1, n - 2);
            int c = rnd.next(1, m - 2);
            g[r][c] = char('1' + rnd.next(9));
        }
    } else if (mode == 3) {
        int n = rnd.next(7, 17);
        int m = rnd.next(7, 19);
        g.assign(n, string(m, '1'));
        int rings = min({(n - 1) / 2, (m - 1) / 2, rnd.next(2, 4)});
        for (int layer = 0; layer < rings; ++layer) {
            char h = char('0' + rnd.next(4, 9));
            for (int c = layer; c < m - layer; ++c) {
                g[layer][c] = h;
                g[n - 1 - layer][c] = h;
            }
            for (int r = layer; r < n - layer; ++r) {
                g[r][layer] = h;
                g[r][m - 1 - layer] = h;
            }
        }
        for (int r = rings; r < n - rings; ++r) {
            for (int c = rings; c < m - rings; ++c) {
                g[r][c] = char('1' + rnd.next(3));
            }
        }
    } else if (mode == 4) {
        int n = rnd.next(4, 15);
        int m = rnd.next(4, 18);
        char wall = char('6' + rnd.next(4));
        char floor = char('1' + rnd.next(3));
        g.assign(n, string(m, wall));
        setRect(g, 1, 1, n - 2, m - 2, floor);

        if (rnd.next(2)) {
            int c = rnd.next(1, m - 2);
            for (int r = 0; r < n; ++r) {
                g[r][c] = floor;
            }
        } else {
            int r = rnd.next(1, n - 2);
            for (int c = 0; c < m; ++c) {
                g[r][c] = floor;
            }
        }
    } else {
        int n = rnd.next(10, 22);
        int m = rnd.next(10, 24);
        g.assign(n, string(m, '1'));
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                int base = 1 + min(8, min({r, c, n - 1 - r, m - 1 - c}));
                int noise = rnd.next(-1, 1);
                int h = max(1, min(9, base + noise));
                g[r][c] = char('0' + h);
            }
        }
    }

    printGrid(g);
    return 0;
}
