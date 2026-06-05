#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

const int MAXC = 2999;

int clampCoord(int x) {
    return max(0, min(MAXC, x));
}

pair<int, int> randomSmallCell() {
    int block = rnd.next(0, 8);
    int xr = rnd.next(0, 2);
    int yr = rnd.next(0, 2);
    return {clampCoord(block * 3 + xr), clampCoord(rnd.next(0, 8) * 3 + yr)};
}

pair<int, int> randomWideCell() {
    int mode = rnd.next(0, 4);
    if (mode == 0) return {rnd.next(0, 12), rnd.next(0, 12)};
    if (mode == 1) return {rnd.next(MAXC - 12, MAXC), rnd.next(MAXC - 12, MAXC)};
    if (mode == 2) return {rnd.next(0, 12), rnd.next(MAXC - 12, MAXC)};
    if (mode == 3) return {rnd.next(MAXC - 12, MAXC), rnd.next(0, 12)};
    return {rnd.next(0, MAXC), rnd.next(0, MAXC)};
}

pair<int, int> cellWithGrundyValue(int value) {
    int p = value / 3;
    int r = value % 3;
    int xp = rnd.next(0, 20);
    int yp = xp ^ p;
    while (yp > 20) {
        xp = rnd.next(0, 20);
        yp = xp ^ p;
    }

    vector<pair<int, int>> residues;
    for (int xr = 0; xr < 3; ++xr) {
        for (int yr = 0; yr < 3; ++yr) {
            if ((xr + yr) % 3 == r) residues.push_back({xr, yr});
        }
    }
    auto [xr, yr] = rnd.any(residues);
    return {xp * 3 + xr, yp * 3 + yr};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    vector<pair<int, int>> cells;

    if (mode == 0) {
        n = 1;
        cells.push_back(randomWideCell());
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        pair<int, int> base = randomWideCell();
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                cells.push_back(randomWideCell());
            } else {
                cells.push_back(base);
            }
        }
    } else if (mode == 2) {
        int w = rnd.next(2, 5);
        int h = rnd.next(2, 5);
        int sx = rnd.next(0, 4);
        int sy = rnd.next(0, 4);
        for (int i = 0; i < w; ++i) {
            for (int j = 0; j < h; ++j) {
                cells.push_back({sx + i, sy + j});
            }
        }
        shuffle(cells.begin(), cells.end());
        cells.resize(rnd.next(1, int(cells.size())));
    } else if (mode == 3) {
        n = rnd.next(2, 16);
        for (int i = 0; i < n; ++i) {
            cells.push_back(randomSmallCell());
        }
    } else if (mode == 4) {
        n = rnd.next(2, 14);
        int value = rnd.next(0, 40);
        for (int i = 0; i < n; ++i) {
            cells.push_back(cellWithGrundyValue(value));
        }
    } else {
        n = rnd.next(2, 20);
        for (int i = 0; i < n; ++i) {
            int value = rnd.next(0, 40);
            cells.push_back(cellWithGrundyValue(value));
        }
    }

    println(int(cells.size()));
    for (auto [x, y] : cells) {
        println(x, y);
    }

    return 0;
}
