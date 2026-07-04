#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

static void addCell(set<pair<int, int>>& cells, int n, int row, int col) {
    row = max(1, min(n, row));
    col = max(1, min(n, col));
    cells.insert({row, col});
}

static pair<int, int> randomCell(int n) {
    return {rnd.next(1, n), rnd.next(1, n)};
}

static vector<pair<int, int>> makeCells(int n, int targetW, int mode) {
    set<pair<int, int>> cells;

    if (mode == 0) {
        int startRow = rnd.next(1, n);
        int startCol = rnd.next(1, n);
        int height = rnd.next(1, min(n, 4));
        int width = rnd.next(1, min(n, 4));
        for (int r = startRow; r < startRow + height && (int)cells.size() < targetW; ++r) {
            for (int c = startCol; c < startCol + width && (int)cells.size() < targetW; ++c) {
                addCell(cells, n, r, c);
            }
        }
    } else if (mode == 1) {
        int row = rnd.next(1, n);
        int col = rnd.next(1, n);
        for (int i = 0; i < n && (int)cells.size() < targetW; ++i) {
            if (rnd.next(0, 1) == 0) {
                addCell(cells, n, row, i + 1);
            } else {
                addCell(cells, n, i + 1, col);
            }
        }
    } else if (mode == 2) {
        for (int i = 1; i <= n && (int)cells.size() < targetW; ++i) {
            addCell(cells, n, i, i);
            if ((int)cells.size() < targetW) {
                addCell(cells, n, i, n + 1 - i);
            }
        }
    }

    while ((int)cells.size() < targetW) {
        cells.insert(randomCell(n));
    }

    vector<pair<int, int>> result(cells.begin(), cells.end());
    shuffle(result.begin(), result.end());
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int z = rnd.next(1, 8);
    println(z);

    for (int tc = 0; tc < z; ++tc) {
        int mode = rnd.next(0, 5);
        int n;
        if (mode == 4) {
            n = rnd.next(50, 2000);
        } else {
            n = rnd.next(1, 12);
        }

        int maxCompactW = min(35, n * n);
        int w;
        if (mode == 3 && n * n >= 8) {
            w = rnd.next(max(1, n * n / 3), min(n * n, 50));
        } else if (mode == 4) {
            w = rnd.next(1, 12);
        } else {
            w = rnd.next(1, maxCompactW);
        }

        int lMode = rnd.next(0, 3);
        int l;
        if (lMode == 0) {
            l = 0;
        } else if (lMode == 1) {
            l = w;
        } else {
            l = rnd.next(0, w);
        }

        vector<pair<int, int>> cells = makeCells(n, w, mode % 3);
        println(n, w, l);
        for (const auto& cell : cells) {
            println(cell.first, cell.second);
        }
    }

    return 0;
}
