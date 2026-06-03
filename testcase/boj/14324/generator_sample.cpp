#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

using Grid = vector<vector<int>>;

Grid randomGrid(int r, int c) {
    int lo = rnd.next(1, 800);
    int hi = rnd.next(lo, 1000);
    Grid g(r, vector<int>(c));
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            g[i][j] = rnd.next(lo, hi);
        }
    }
    return g;
}

Grid slopeGrid(int r, int c) {
    int base = rnd.next(1, 700);
    int rowStep = rnd.next(0, 30);
    int colStep = rnd.next(0, 30);
    Grid g(r, vector<int>(c));
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            int value = base + i * rowStep + j * colStep + rnd.next(0, 3);
            g[i][j] = min(value, 1000);
        }
    }
    if (rnd.next(2)) {
        reverse(g.begin(), g.end());
    }
    if (rnd.next(2)) {
        for (auto& row : g) {
            reverse(row.begin(), row.end());
        }
    }
    return g;
}

Grid basinGrid(int r, int c) {
    int wall = rnd.next(20, 1000);
    int floor = rnd.next(1, wall);
    Grid g(r, vector<int>(c, wall));

    if (r >= 3 && c >= 3) {
        for (int i = 1; i + 1 < r; ++i) {
            for (int j = 1; j + 1 < c; ++j) {
                g[i][j] = rnd.next(floor, wall);
            }
        }

        int pockets = rnd.next(1, min(5, (r - 2) * (c - 2)));
        for (int k = 0; k < pockets; ++k) {
            int i = rnd.next(1, r - 2);
            int j = rnd.next(1, c - 2);
            g[i][j] = rnd.next(1, floor);
        }

        if (rnd.next(3) == 0) {
            int side = rnd.next(4);
            int pos = (side < 2 ? rnd.next(c) : rnd.next(r));
            int leak = rnd.next(1, wall);
            if (side == 0) g[0][pos] = leak;
            if (side == 1) g[r - 1][pos] = leak;
            if (side == 2) g[pos][0] = leak;
            if (side == 3) g[pos][c - 1] = leak;
        }
    }

    return g;
}

Grid stripedGrid(int r, int c) {
    Grid g(r, vector<int>(c));
    int a = rnd.next(1, 500);
    int b = rnd.next(a, 1000);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            g[i][j] = ((i + j + rnd.next(2)) % 2 == 0) ? a : b;
        }
    }
    return g;
}

void printGrid(const Grid& g) {
    println((int)g.size(), (int)g[0].size());
    for (const auto& row : g) {
        println(row);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 8);
    println(t);

    for (int caseIndex = 0; caseIndex < t; ++caseIndex) {
        int mode = rnd.next(5);
        int r = 1, c = 1;

        if (mode == 0) {
            r = rnd.next(1, 2);
            c = rnd.next(1, 10);
            if (rnd.next(2)) swap(r, c);
        } else if (mode == 1) {
            r = rnd.next(2, 5);
            c = rnd.next(2, 5);
        } else {
            r = rnd.next(3, 10);
            c = rnd.next(3, 10);
        }

        Grid g;
        if (mode == 0) {
            g = randomGrid(r, c);
        } else if (mode == 1) {
            g = stripedGrid(r, c);
        } else if (mode == 2) {
            g = slopeGrid(r, c);
        } else {
            g = basinGrid(r, c);
        }
        printGrid(g);
    }

    return 0;
}
