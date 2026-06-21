#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

string coord(int whole, int fracTenths) {
    return toString(whole) + "." + toString(fracTenths);
}

pair<string, string> pointInCell(int xCell, int yCell) {
    return {coord(xCell, rnd.next(1, 9)), coord(yCell, rnd.next(1, 9))};
}

vector<pair<int, int>> buildCells(int n, int m, int mode) {
    vector<pair<int, int>> cells;

    if (mode == 0) {
        int x = rnd.next(0, n - 1);
        int k = rnd.next(1, min(m, 10));
        vector<int> ys;
        for (int y = 0; y < m; ++y) ys.push_back(y);
        shuffle(ys.begin(), ys.end());
        for (int i = 0; i < k; ++i) cells.push_back({x, ys[i]});
    } else if (mode == 1) {
        int y = rnd.next(0, m - 1);
        int k = rnd.next(1, min(n, 10));
        vector<int> xs;
        for (int x = 0; x < n; ++x) xs.push_back(x);
        shuffle(xs.begin(), xs.end());
        for (int i = 0; i < k; ++i) cells.push_back({xs[i], y});
    } else if (mode == 2) {
        int k = rnd.next(1, min({n, m, 12}));
        vector<int> xs, ys;
        for (int x = 0; x < n; ++x) xs.push_back(x);
        for (int y = 0; y < m; ++y) ys.push_back(y);
        shuffle(xs.begin(), xs.end());
        shuffle(ys.begin(), ys.end());
        for (int i = 0; i < k; ++i) cells.push_back({xs[i], ys[i]});
    } else if (mode == 3) {
        int rows = rnd.next(1, min(n, 5));
        int cols = rnd.next(1, min(m, 5));
        int x0 = rnd.next(0, n - rows);
        int y0 = rnd.next(0, m - cols);
        for (int x = x0; x < x0 + rows; ++x) {
            for (int y = y0; y < y0 + cols; ++y) {
                if (rnd.next(0, 99) < 65) cells.push_back({x, y});
            }
        }
        if (cells.empty()) cells.push_back({x0, y0});
    } else {
        int limit = min(n * m, 35);
        int k = rnd.next(1, limit);
        vector<pair<int, int>> all;
        for (int x = 0; x < n; ++x) {
            for (int y = 0; y < m; ++y) all.push_back({x, y});
        }
        shuffle(all.begin(), all.end());
        cells.assign(all.begin(), all.begin() + k);
    }

    int duplicates = rnd.next(0, min(5, static_cast<int>(cells.size())));
    for (int i = 0; i < duplicates; ++i) cells.push_back(rnd.any(cells));
    shuffle(cells.begin(), cells.end());
    return cells;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int r = rnd.next(1, 6);
    println(r);

    for (int tc = 0; tc < r; ++tc) {
        int mode = rnd.next(0, 4);
        int n = rnd.next(1, 12);
        int m = rnd.next(1, 12);

        if (rnd.next(0, 9) == 0) n = rnd.next(80, 100);
        if (rnd.next(0, 9) == 0) m = rnd.next(80, 100);

        vector<pair<int, int>> cells = buildCells(n, m, mode);
        println(n, m, static_cast<int>(cells.size()));
        for (auto cell : cells) {
            auto p = pointInCell(cell.first, cell.second);
            println(p.first, p.second);
        }
    }

    return 0;
}
