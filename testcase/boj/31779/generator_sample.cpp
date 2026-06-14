#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 7);
    int m = rnd.next(1, 7);
    if (mode == 1) n = 1;
    if (mode == 2) m = 1;
    if (mode == 3) {
        n = rnd.next(2, 5);
        m = rnd.next(2, 5);
    }

    vector<vector<long long>> a(n, vector<long long>(m));
    vector<vector<long long>> b(n, vector<long long>(m));
    int valueMode = rnd.next(0, 3);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (valueMode == 0) {
                a[i][j] = rnd.next(-5, 5);
                b[i][j] = a[i][j] + rnd.next(-4, 4);
            } else if (valueMode == 1) {
                a[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * rnd.next(0, 20);
                b[i][j] = ((i + j) % 2 == 0 ? -1 : 1) * rnd.next(0, 20);
            } else {
                long long base = rnd.any(vector<long long>{-1000000000LL, -999999999LL, 999999999LL, 1000000000LL});
                a[i][j] = base;
                b[i][j] = max(-1000000000LL, min(1000000000LL, base + rnd.next(-3, 3)));
            }
        }
    }

    vector<pair<int, int>> cells;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            bool take = false;
            if (mode == 0) take = rnd.next(0, 4) == 0;
            if (mode == 1 || mode == 2) take = rnd.next(0, 2) == 0;
            if (mode == 3) take = (i + j) % 2 == rnd.next(0, 1);
            if (mode == 4) take = true;
            if (mode == 5) take = rnd.next(0, 9) < 7;
            if (take) cells.push_back({i + 1, j + 1});
        }
    }
    shuffle(cells.begin(), cells.end());

    if (!cells.empty() && rnd.next(0, 1) == 0) {
        int keep = rnd.next(0, (int)cells.size());
        cells.resize(keep);
    }

    if (rnd.next(0, 2) != 0) {
        for (auto [x, y] : cells) {
            b[x - 1][y - 1] = a[x - 1][y - 1];
        }
    }

    println(n, m, (int)cells.size());
    for (int i = 0; i < n; ++i) println(a[i]);
    for (int i = 0; i < n; ++i) println(b[i]);
    for (auto [x, y] : cells) println(x, y);

    return 0;
}
