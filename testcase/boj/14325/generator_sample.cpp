#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

vector<vector<int>> makeFlat(int r, int c) {
    int h = rnd.next(1, 1000);
    return vector<vector<int>>(r, vector<int>(c, h));
}

vector<vector<int>> makeSlope(int r, int c) {
    int base = rnd.next(1, 25);
    int rowStep = rnd.next(0, 7);
    int colStep = rnd.next(0, 7);
    vector<vector<int>> a(r, vector<int>(c));
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            a[i][j] = min(1000, base + i * rowStep + j * colStep + rnd.next(0, 3));
        }
    }
    return a;
}

vector<vector<int>> makeBowl(int r, int c) {
    int wall = rnd.next(5, 40);
    int floor = rnd.next(1, wall - 1);
    vector<vector<int>> a(r, vector<int>(c, wall));
    if (r <= 2 || c <= 2) {
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                a[i][j] = rnd.next(1, wall);
            }
        }
        return a;
    }

    for (int i = 1; i + 1 < r; ++i) {
        for (int j = 1; j + 1 < c; ++j) {
            a[i][j] = rnd.next(floor, wall - 1);
        }
    }

    if (rnd.next(2) == 0) {
        int side = rnd.next(4);
        if (side == 0) a[0][rnd.next(c)] = rnd.next(1, wall);
        if (side == 1) a[r - 1][rnd.next(c)] = rnd.next(1, wall);
        if (side == 2) a[rnd.next(r)][0] = rnd.next(1, wall);
        if (side == 3) a[rnd.next(r)][c - 1] = rnd.next(1, wall);
    }
    return a;
}

vector<vector<int>> makeNested(int r, int c) {
    vector<vector<int>> a(r, vector<int>(c));
    int outer = rnd.next(20, 70);
    int inner = rnd.next(1, outer - 1);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            int d = min(min(i, r - 1 - i), min(j, c - 1 - j));
            int h = outer - d * rnd.next(3, 8);
            a[i][j] = max(inner, h + rnd.next(-1, 1));
        }
    }
    return a;
}

vector<vector<int>> makeRandomGrid(int r, int c) {
    int lo = rnd.next(1, 20);
    int hi = rnd.next(lo, min(1000, lo + rnd.next(5, 80)));
    vector<vector<int>> a(r, vector<int>(c));
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            a[i][j] = rnd.next(lo, hi);
        }
    }
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(5, 12);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(5);
        int r, c;
        if (mode == 0) {
            if (rnd.next(2) == 0) {
                r = 1;
                c = rnd.next(1, 12);
            } else {
                r = rnd.next(1, 12);
                c = 1;
            }
        } else {
            r = rnd.next(2, 9);
            c = rnd.next(2, 9);
        }

        vector<vector<int>> grid;
        if (mode == 0) {
            grid = makeSlope(r, c);
        } else if (mode == 1) {
            grid = makeFlat(r, c);
        } else if (mode == 2) {
            grid = makeBowl(r, c);
        } else if (mode == 3) {
            grid = makeNested(r, c);
        } else {
            grid = makeRandomGrid(r, c);
        }

        println(r, c);
        for (int i = 0; i < r; ++i) {
            println(grid[i]);
        }
    }

    return 0;
}
